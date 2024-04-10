#####################################################################
# Copyright (C) Meteor Engine contributors, all rights reserved.
#####################################################################

cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17 REQUIRED)
project("ThirdParty")

# glm
set(SDK_VERSION "0.9.9.9")
add_library(glm INTERFACE)
set(GLM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glm/${SDK_VERSION})
target_sources(glm INTERFACE ${GLM_DIR}/glm/glm.hpp)

target_include_directories(glm INTERFACE ${GLM_DIR})
target_compile_definitions(glm INTERFACE
  GLM_FORCE_SWIZZLE
  GLM_FORCE_RADIANS
  GLM_FORCE_CTOR_INIT
  GLM_ENABLE_EXPERIMENTAL
)

# vulkan
set(SDK_VERSION "1.3.270")
add_library(vulkan INTERFACE)
set(VULKAN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vulkan/${SDK_VERSION}/include)
target_sources(vulkan INTERFACE ${VULKAN_INCLUDE_DIR}/vulkan/vulkan.h)

target_include_directories(vulkan INTERFACE ${VULKAN_INCLUDE_DIR})
target_compile_definitions(vulkan INTERFACE VK_NO_PROTOTYPES)

# volk
set(SDK_VERSION "1.3.270")
set(VOLK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/volk/${SDK_VERSION})
set(VOLK_SRC "${VOLK_DIR}/volk.c" "${VOLK_DIR}/volk.h")

add_library(volk STATIC ${VOLK_SRC})
target_link_libraries(volk vulkan)

target_include_directories(volk PUBLIC ${VOLK_DIR})
if (ME_USE_WAYLAND_BACKEND)
  target_include_directories(volk PUBLIC ${WAYLAND_INCLUDE_DIRS})
endif()
set_target_properties(volk PROPERTIES POSITION_INDEPENDENT_CODE ON FOLDER "ThirdParty")

# glfw (Windows, Linux, macOS)
if (NOT ANDROID)
  set(SDK_VERSION "3.3.8")
  option(GLFW_BUILD_DOCS OFF)
  option(GLFW_BUILD_TESTS OFF)
  option(GLFW_BUILD_EXAMPLES OFF)
  option(GLFW_INSTALL OFF)
  if (ME_USE_WAYLAND_BACKEND)
    set(GLFW_USE_WAYLAND ON)
  endif()

  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw/${SDK_VERSION})
  set_property(TARGET glfw PROPERTY FOLDER "ThirdParty")
endif()
