/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

/**
 * @file    VulkanInstance.cpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Renderer: Vulkan physical device
 */

#include "API/VulkanCommon.hpp"
#include "API/VulkanInstance.hpp"
#include "API/VulkanPhysicalDevice.hpp"

namespace ME::Render::Vulkan
{
  PhysicalDevice::PhysicalDevice(Instance& instance, VkPhysicalDevice physicalDevice) :
    m_instance(instance),
    m_physicalDevice(physicalDevice)
  {
    uint32_t extensionCount = 0;
    VK_CHECK(::vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, nullptr));

    m_extensions.resize(extensionCount);
    VK_CHECK(::vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, m_extensions.data()));
  }

  bool PhysicalDevice::IsExtensionPresent(const char* extensionName)
  {
    auto iter = std::find_if(m_extensions.begin(), m_extensions.end(), [&](const VkExtensionProperties& extension)
    {
      return strcmp(extension.extensionName, extensionName) == 0;
    });

    return iter != m_extensions.end();
  }
} // namespace ME::Render::Vulkan
