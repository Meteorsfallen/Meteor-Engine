/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

/**
 * @file    VulkanDevice.cpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Render: Logical device
 */

#include "API/VulkanCommon.hpp"
#include "API/VulkanPhysicalDevice.hpp"
#include "API/VulkanQueue.hpp"
#include "API/VulkanDevice.hpp"

namespace ME::Render::Vulkan
{
  namespace Internal
  {
    struct QueueCache
    {
    };
  }

  Device::Device(PhysicalDevice& physicalDevice) :
    m_physicalDevice(physicalDevice)
  {
    
  }

  Device::~Device()
  {
    ::vkDeviceWaitIdle(m_device);

    if (m_device)
    {
      ::vkDestroyDevice(m_device, nullptr);
      m_device = VK_NULL_HANDLE;
    }
  }

  bool Device::RequestExtension(const char* extensionName)
  {
    if (m_physicalDevice.IsExtensionPresent(extensionName))
    {
      m_extensions.emplace_back(extensionName);
      return true;
    }

    return false;
  }

  void Device::Create()
  {

  }
} // namespace ME::Render::Vulkan
