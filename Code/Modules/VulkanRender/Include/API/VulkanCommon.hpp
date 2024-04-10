/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#pragma once

/**
 * @file    VulkanCommon.hpp
 * @author  Liu Xinyu
 * 
 * @brief
 * Common definitions/types/utilities for Vulkan render
 */

#include <EngineTypes.hpp>

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include <volk.h>

#define VK_CHECK(vkr)                                       \
  if (vkr != VK_SUCCESS)                                    \
  {                                                         \
    throw Exception(vkr, "Vulkan error: "#vkr" - FAILED");  \
  }

#define VK_LOGI(...)
#define VK_LOGW(...)
#define VK_LOGE(...)
#define VK_LOGC(...)

namespace ME::Render::Vulkan
{
  template <typename T>
  inline constexpr uint32_t to_u32(T value)
  {
    return static_cast<uint32_t>(value);
  }

  class Exception : public std::runtime_error
  {
    VkResult    m_result{ VK_ERROR_UNKNOWN };
    std::string m_msg;
  public:
    ME_FORCEINLINE Exception(VkResult vkr, const std::string& msg) : std::runtime_error(msg), m_result(vkr)
    {
      m_msg = msg;
    }
    ME_FORCEINLINE const char* what() const noexcept override
    {
      return m_msg.c_str();
    }
  };
} // namespace ME::Render::Vulkan
