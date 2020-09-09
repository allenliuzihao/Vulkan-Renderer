#ifndef Renderer_hpp
#define Renderer_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <unordered_set>

#include "Utilities.h"

class Renderer{
public:
    void init();
    void cleanUp();

private:
    // vulkan instance
    VkInstance instance;
    
    // debugger
    VkDebugUtilsMessengerEXT debugMessenger;
    
    void createInstance();
    
    std::vector<const char*> getRequiredExtensions();
    
    bool checkExtensionsSupport(const std::vector<const char*> & requiredExtensions);
    bool checkValidationLayerSupport();
    
    void setUpDebugMessenger();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                          const VkAllocationCallbacks* pAllocator,
                                          VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugMessageFunc(VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
                                                           VkDebugUtilsMessageTypeFlagsEXT              messageTypes,
                                                           VkDebugUtilsMessengerCallbackDataEXT const * pCallbackData,
                                                           void* pUserData);
};

#endif /* Renderer_hpp */
