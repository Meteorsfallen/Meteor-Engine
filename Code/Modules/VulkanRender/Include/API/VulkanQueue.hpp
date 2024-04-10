/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    VulkanQueue.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Vulkan Render: Command queue
 */

/**
 * 据说 D3D12 的命令队列是软实现，Vulkan 的命令队列是硬实现，那是不是 Vulkan 的队列效率
 * 在极致的优化下会比 D3D12 的高？不过就目前的情况来看，因为一个软一个硬，命令队列的部分
 * 不能统一实现了。
 */

namespace ME::Render::Vulkan
{
  class Device;
  class Queue
  {
  public:
    Queue(Device& device, uint32 queueFamilyIndex, uint32 queueIndex, VkBool32 presentSupport, VkQueue queue);
    ~Queue() {}

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&&);

    VkResult Submit(const TVector<VkSubmitInfo>& submitInfos, VkFence fence);
    VkResult Present(const VkPresentInfoKHR& presentInfo);

    inline VkQueue GetHandle() const { return m_queue; }

  private:
    Device& m_device;

    uint32    m_queueFamilyIndex;
    uint32    m_queueIndex;
    VkBool32  m_presentSupport;

    VkQueue   m_queue;
  };
} // namespace ME::Render::Vulkan
