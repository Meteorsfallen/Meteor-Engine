#####################################################################
# Copyright (C) Meteor Engine contributors, all rights reserved.
#####################################################################

file(GLOB_RECURSE EXE_SOURCES src/*.*)
add_executable(VulkanRenderTest ${EXE_SOURCES})

target_link_libraries(VulkanRenderTest ME::VulkanRender)
set_target_properties(VulkanRenderTest PROPERTIES FOLDER "Tests")
