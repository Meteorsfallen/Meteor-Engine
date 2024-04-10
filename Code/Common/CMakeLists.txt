#####################################################################
# Copyright (C) Meteor Engine contributors, all rights reserved.
#####################################################################

if (MSVC)
  set(LIB_NAME "MeteorCommon")  # MeteorCommon.lib (.dll)
else()
  set(LIB_NAME "meteor-common") # libmeteor-common.a (.so)
endif()

file(GLOB_RECURSE LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.hpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/${ME_TARGET_PLATFORM}/*.hpp)

file(GLOB_RECURSE LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp
                              ${CMAKE_CURRENT_SOURCE_DIR}/${ME_TARGET_PLATFORM}/*.cpp)

if (BUILD_SHARED_LIBS)
  add_library(${LIB_NAME} SHARED ${LIB_HEADERS} ${LIB_SOURCES})
else()
  add_library(${LIB_NAME} STATIC ${LIB_HEADERS} ${LIB_SOURCES})
endif()

set(LIB_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include
                ${CMAKE_CURRENT_SOURCE_DIR}/${ME_TARGET_PLATFORM})
target_include_directories(${LIB_NAME} PUBLIC ${LIB_INC_DIR})

# ALIAS
add_library(ME::Common ALIAS ${LIB_NAME})
