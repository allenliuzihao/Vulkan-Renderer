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

#include <optional>
#include <unordered_set>

#include "Utilities.h"

class Renderer{
public:
    void init();
    void cleanUp();

private:
    // vulkan instance
    VkInstance instance;
    
    // GPU instance
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    
    // vulkan queues
    VkQueue graphicsQueue;
    
    void createInstance();
    void createLogicalDevice();
    
    // devices
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    void selectPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    
    std::vector<const char*> getRequiredExtensions();
    
    bool checkExtensionsSupport(const std::vector<const char*> & requiredExtensions);
    bool checkValidationLayerSupport();
    
    // debugger
    VkDebugUtilsMessengerEXT debugMessenger;
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
