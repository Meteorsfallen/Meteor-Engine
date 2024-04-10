/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

/**
 * @file    VulkanInstance.cpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Render: Vulkan instance
 */

#include "API\VulkanCommon.hpp"
#include "API\VulkanInstance.hpp"
#include "API\VulkanPhysicalDevice.hpp"

namespace ME::Render::Vulkan
{
#if defined(ME_DEBUG) || defined(_DEBUG)
  static VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
  {
    switch(messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
      VK_LOGW("%s", pCallbackData->pMessage);
      break;
    
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
      VK_LOGE("%s", pCallbackData->pMessage);
      break;
    
    default:
      VK_LOGI("%s", pCallbackData->pMessage);
    }
    return VK_FALSE;
  }

  static VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(
    VkDebugReportFlagsEXT flags,
    VkDebugReportObjectTypeEXT objectType,
    uint64_t object,
    size_t location,
    int32_t messageCode,
    const char* pLayerPrefix,
    const char* pMessage,
    void* pUserData)
  {
    // TODO:
    return VK_FALSE;
  }
#endif
  Instance::Instance()
  {
    // volkInitialize 就不在此处调用了，保证结构规范!
    if (!::vkCreateInstance)
    {
      throw Exception(VK_ERROR_INITIALIZATION_FAILED, "Vulkan not available");
    }

    // Vulkan API 版本
    m_apiVersion = ::volkGetInstanceVersion();

    // 层属性
    uint32_t layerCount = 0;
    VK_CHECK(::vkEnumerateInstanceLayerProperties(&layerCount, nullptr));
    //
    m_layerProperties.resize(layerCount);
    VK_CHECK(::vkEnumerateInstanceLayerProperties(&layerCount, m_layerProperties.data()));

    // 扩展属性
    uint32_t extensionCount = 0;
    VK_CHECK(::vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr));
    //
    m_extensionProperties.resize(extensionCount);
    VK_CHECK(::vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, m_extensionProperties.data()));
  }

  Instance::~Instance()
  {
    if (!m_instance)
    {
      return;
    }

#if defined(ME_DEBUG) || defined(_DEBUG)
    if (m_debugUtilsMessenger)
    {
      ::vkDestroyDebugUtilsMessengerEXT(m_instance, m_debugUtilsMessenger, nullptr);
      m_debugUtilsMessenger = VK_NULL_HANDLE;
    }

    if (m_debugReportCallback)
    {
      ::vkDestroyDebugReportCallbackEXT(m_instance, m_debugReportCallback, nullptr);
      m_debugReportCallback = VK_NULL_HANDLE;
    }
#endif
    ::vkDestroyInstance(m_instance, nullptr);
    m_instance = VK_NULL_HANDLE;
  }

  Instance::Instance(Instance&& other)
  {
    // 这里变更所有权的过程, 在本人写的代码中应该是不会调用的，毕竟 Vulkan 规范中
    // 要求，一个进程只需要一个 Vulkan 实例。同时，类似的关系还有，一个物理设备对应
    // 一个逻辑设备。
    //
    // 但是这里还是加上了，如果有憨憨不知道这个规范，真正调用了，还是得该咋做咋做的，
    // 有规矩总是好事。
    if (m_instance)
    {
      ::vkDestroyInstance(m_instance, nullptr);
    }

    m_instance = other.m_instance;
    // 自此，原对象不再具有所有权，如果操作不当，这里就出现了一个野生的句柄。
    other.m_instance = VK_NULL_HANDLE;
  }

  bool Instance::RequestLayer(const char* layerName)
  {
    auto iter = std::find_if(m_layerProperties.begin(), m_layerProperties.end(), [layerName](const VkLayerProperties& layer) {
      return 0 == strcmp(layer.layerName, layerName);
    });

    if (iter != m_layerProperties.end())
    {
      m_requestedLayers.emplace_back(layerName);
      return true;
    }

    return false;
  }

  bool Instance::RequestExtension(const char* extensionName)
  {
    auto iter = std::find_if(m_extensionProperties.begin(), m_extensionProperties.end(), [extensionName](const VkExtensionProperties& extension) {
      return 0 == strcmp(extension.extensionName, extensionName);
    });

    if (iter != m_extensionProperties.end())
    {
      m_requestedExtensions.emplace_back(extensionName);
      return true;
    }

    return false;
  }

  void Instance::Create(const VkApplicationInfo& appInfo)
  {
#if defined(ME_DEBUG) || defined(_DEBUG)
    if (!RequestLayer("VK_LAYER_KHRONOS_validation"))
    {
      VK_LOGW("Validation layer not available");
    }
#endif

    // VK_KHR_get_physical_device_properties2
    if (!RequestExtension(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME))
    {
      VK_LOGW("'VK_KHR_get_physical_device_properties2' extension not available");
    }

    VkInstanceCreateInfo createInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    createInfo.pApplicationInfo         = &appInfo;
    createInfo.enabledLayerCount        = to_u32(m_requestedLayers.size());
    createInfo.ppEnabledLayerNames      = m_requestedLayers.data();
    createInfo.enabledExtensionCount    = to_u32(m_requestedExtensions.size());
    createInfo.ppEnabledExtensionNames  = m_requestedExtensions.data();

#if defined(ME_DEBUG) || defined(_DEBUG)
    bool debugUtils = RequestExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    bool debugReport{ false };
    if (!debugUtils)
    {
      debugReport = RequestExtension(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    VkDebugUtilsMessengerCreateInfoEXT debugUtilsInfo{ VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
    VkDebugReportCallbackCreateInfoEXT debugReportInfo{ VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };

    if (debugUtils)
    {
      debugUtilsInfo.messageType      = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
      debugUtilsInfo.messageSeverity  = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
      debugUtilsInfo.pUserData        = this;
      debugUtilsInfo.pfnUserCallback  = DebugUtilsMessengerCallback;
      //
      createInfo.pNext = &debugUtilsInfo;
    }

    if (debugReport)
    {
      debugReportInfo.flags       = VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT;
      debugReportInfo.pfnCallback = DebugReportCallback;
      debugReportInfo.pUserData   = this;
      //
      createInfo.pNext = &debugReportInfo;
    }
#endif

    VkResult r = ::vkCreateInstance(&createInfo, nullptr, &m_instance);
    if (r != VK_SUCCESS)
    {
      throw Exception(r, "Failed to create Vulkan instance");
    }

    ::volkLoadInstance(m_instance);

#if defined(ME_DEBUG) || defined(_DEBUG)
    if (debugUtils)
    {
      r = ::vkCreateDebugUtilsMessengerEXT(m_instance, &debugUtilsInfo, nullptr, &m_debugUtilsMessenger);
      if (r != VK_SUCCESS)
      {
        throw Exception(r, "Failed to create Vulkan debug utils messenger");
      }
    }

    if (debugReport)
    {
      r = ::vkCreateDebugReportCallbackEXT(m_instance, &debugReportInfo, nullptr, &m_debugReportCallback);
      if (r != VK_SUCCESS)
      {
        throw Exception(r, "Failed to create Vulkan debug report callback");
      }
    }
#endif
  }

  uint32 Instance::QueryPhysicalDevice()
  {
    uint32_t physicalDeviceCount = 0;
    VK_CHECK(::vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, nullptr));

    TVector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    VK_CHECK(::vkEnumeratePhysicalDevices(m_instance, &physicalDeviceCount, physicalDevices.data()));

    for (const auto& physicalDevice : physicalDevices)
    {
      m_physicalDevices.emplace_back(new PhysicalDevice(*this, physicalDevice));
    }

    return physicalDeviceCount;
  }

  PhysicalDevice* Instance::GetPhysicalDevice(uint32 index)
  {
    return m_physicalDevices.at(index);
  }
} // namespace ME::Render::Vulkan
