/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    VulkanInstance.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Renderer: Vulkan physical device
 */

namespace ME::Render::Vulkan
{
  class Instance;
  class PhysicalDevice
  {
  public:
    PhysicalDevice(Instance& instance, VkPhysicalDevice physicalDevice);
    ~PhysicalDevice() {}

    bool IsExtensionPresent(const char* extensionName);

    inline VkPhysicalDevice GetHandle() const { return m_physicalDevice; }

  private:
    Instance& m_instance;

    VkPhysicalDevice m_physicalDevice{ VK_NULL_HANDLE };

    TVector<VkExtensionProperties> m_extensions;
  };
} // namespace ME::Render::Vulkan
