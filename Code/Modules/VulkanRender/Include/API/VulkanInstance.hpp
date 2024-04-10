/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    VulkanInstance.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Render: Vulkan instance
 */

namespace ME::Render::Vulkan
{
  class PhysicalDevice;
  class Instance
  {
  public:
    Instance();
    ~Instance();

    Instance(const Instance&) = delete;
    Instance& operator= (const Instance&) = delete;

    Instance(Instance&&);

    bool RequestLayer(const char* layerName);
    bool RequestExtension(const char* extensionName);

    void Create(const VkApplicationInfo& appInfo);

    uint32 QueryPhysicalDevice();
    PhysicalDevice* GetPhysicalDevice(uint32 index);

    inline const TVector<PhysicalDevice*>& GetPhysicalDevices() { return m_physicalDevices; }
    
    inline VkInstance GetHandle() const { return m_instance; }

  private:
    uint32     m_apiVersion;
    VkInstance m_instance{ VK_NULL_HANDLE };

    TVector<VkLayerProperties>      m_layerProperties;
    TVector<VkExtensionProperties>  m_extensionProperties;

    TVector<const char*> m_requestedLayers;
    TVector<const char*> m_requestedExtensions; 

    TVector<PhysicalDevice*> m_physicalDevices;

#if defined(ME_DEBUG) || defined(_DEBUG)
    VkDebugUtilsMessengerEXT m_debugUtilsMessenger{ VK_NULL_HANDLE };
    VkDebugReportCallbackEXT m_debugReportCallback{ VK_NULL_HANDLE };
#endif
  };
} // namespace ME::Render::Vulkan
