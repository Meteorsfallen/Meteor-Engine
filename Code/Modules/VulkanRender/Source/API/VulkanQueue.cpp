/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    VulkanQueue.cpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Render: Command queue
 */

#include "API/VulkanCommon.hpp"
#include "API/VulkanQueue.hpp"

namespace ME::Render::Vulkan
{
  Queue::Queue(Device& device, uint32 queueFamilyIndex, uint32 queueIndex, VkBool32 presentSupport, VkQueue queue) :
    m_device(device),
    m_queueFamilyIndex(queueFamilyIndex),
    m_queueIndex(queueIndex),
    m_presentSupport(presentSupport),
    m_queue(queue)
  {
  }

  Queue::Queue(Queue&& other) :
    m_device(other.m_device),
    m_queueFamilyIndex(other.m_queueFamilyIndex),
    m_queueIndex(other.m_queueIndex),
    m_presentSupport(other.m_presentSupport),
    m_queue(other.m_queue)
  {
    other.m_queue = VK_NULL_HANDLE;
  }

  VkResult Queue::Submit(const TVector<VkSubmitInfo>& submitInfos, VkFence fence)
  {
    return ::vkQueueSubmit(m_queue, to_u32(submitInfos.size()), submitInfos.data(), fence);
  }

  VkResult Queue::Present(const VkPresentInfoKHR& presentInfo)
  {
    return ::vkQueuePresentKHR(m_queue, &presentInfo);
  }
} // namespace ME::Render::Vulkan
