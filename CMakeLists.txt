#####################################################################
# Copyright (C) Meteor Engine contributors, all rights reserved.
#####################################################################

set(ME_VERSION_MAJOR 0)
set(ME_VERSION_MINOR 0)
set(ME_VERSION_PATCH 0)

cmake_minimum_required(VERSION 3.22)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17 REQUIRED)
project("MeteorEngine")

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "不支持 32 位系统")
endif()
# UTF-8 IN MSVC
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if (NOT DEFINED CMAKE_BUILD_TYPE AND NOT MSVC)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# 由于 GCC 还没有加上用于判断调试模式相关的宏，所以...
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(ME_DEBUG)
endif()

if (NOT DEFINED ME_TARGET_PLATFORM)
  if (WIN32)
    set(ME_TARGET_PLATFORM "Windows")
  elseif (APPLE)
    set(ME_TARGET_PLATFORM "macOS")
  elseif (UNIX)
    set(ME_TARGET_PLATFORM "Linux")
  endif()
endif()

message(STATUS "Configure for target platform: ${ME_TARGET_PLATFORM}")

if (MSVC)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Output/Lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Output/Bin)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Output/Bin)
else()
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Output/Lib/${CMAKE_BUILD_TYPE})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Output/Bin/${CMAKE_BUILD_TYPE})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/Output/Bin/${CMAKE_BUILD_TYPE})
endif()

set(ME_CONFIG_DIR ${PROJECT_BINARY_DIR}/Config)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/MeteorConfig.hpp.in ${ME_CONFIG_DIR}/MeteorConfig.hpp)
include_directories(${ME_CONFIG_DIR})

add_subdirectory(ThirdParty)
add_subdirectory(Code)
add_subdirectory(Plugins)
add_subdirectory(Tests)
