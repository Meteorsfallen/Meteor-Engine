/////////////////////////////////////////////////////////////////////
// Copyright (C) Meteor Engine contributors, all rights reserved.
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <volk.h>

int main()
{
  auto r = volkInitialize();
  if (r != VK_SUCCESS)
  {
    printf("Failed to initialize Vulkan APIs\n");
  }

  uint32_t apiVersion = volkGetInstanceVersion();
  VkApplicationInfo appInfo{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
  appInfo.apiVersion = apiVersion;

  VkInstanceCreateInfo createInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
  createInfo.pApplicationInfo = &appInfo;

  VkInstance instance{ VK_NULL_HANDLE };
  r = ::vkCreateInstance(&createInfo, nullptr, &instance);
  if (r != VK_SUCCESS)
  {
    printf("Failed to create Vulkan instance\n");
    return -1;
  }

  ::vkDestroyInstance(instance, nullptr);
  volkFinalize();
  return 0;
}
