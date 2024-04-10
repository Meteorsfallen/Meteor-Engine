#####################################################################
# Copyright (C) Meteor Engine contributors, all rights reserved.
#####################################################################

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)

file(GLOB_RECURSE MODULE_HEADERS ${INC_DIR}/*.hpp ${ME_TARGET_PLATFORM}/*.hpp)
file(GLOB_RECURSE MODULE_SOURCES ${SRC_DIR}/*.cpp ${ME_TARGET_PLATFORM}/*.cpp)

if (MSVC)
  set(LIB_NAME "ME.VulkanRender")
else()
  set(LIB_NAME "meteor-vulkan")
endif()

if (BUILD_SHARED_LIBS)
  add_library(${LIB_NAME} SHARED ${MODULE_HEADERS} ${MODULE_SOURCES})
else()
  add_library(${LIB_NAME} STATIC ${MODULE_HEADERS} ${MODULE_SOURCES})
endif()

target_link_libraries(${LIB_NAME} vulkan volk ME::Common)

target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR} ${ME_TARGET_PLATFORM})
target_compile_definitions(${LIB_NAME} PUBLIC VK_NO_PROTOTYPES)

# ALIAS
add_library(ME::VulkanRender ALIAS ${LIB_NAME})
