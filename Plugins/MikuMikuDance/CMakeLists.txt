#####################################################################
# Copyright (C) Meteor Engine contributors, all rights reserved.
#####################################################################

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Include/*.*)
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.*)

if (MSVC)
  set(PLUGIN_NAME "ME.MikuMikuDance")
else()
  set(PLUGIN_NAME "meteor-mmd")
endif()

add_library(${PLUGIN_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PLUGIN_NAME} ME::Common)
