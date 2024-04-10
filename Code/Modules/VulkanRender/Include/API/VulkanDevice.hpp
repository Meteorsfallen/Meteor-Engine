/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    VulkanDevice.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Render: Logical device
 */

namespace ME::Render::Vulkan
{
  class PhysicalDevice;
  class Device
  {
  public:
    Device(PhysicalDevice& physicalDevice);
    ~Device();

    bool RequestExtension(const char* extensionName);

    void Create();

  private:
    PhysicalDevice& m_physicalDevice;

    TVector<const char*> m_extensions;

    VkDevice m_device{ VK_NULL_HANDLE };
  };
} // namespace ME::Render::Vulkan
