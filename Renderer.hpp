#ifndef Renderer_hpp
#define Renderer_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include <cstdlib>
#include <cstdint> // Necessary for UINT32_MAX
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <unordered_set>

#include "Utilities.h"

class Renderer{
public:
    void init(GLFWwindow* window);
    void cleanUp();

private:    
    // vulkan instance
    VkInstance instance;
    
    // GPU instance
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    
    // vulkan queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    
    // surface
    VkSurfaceKHR surface;
    
    // swapchain
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    
    void createInstance();
    void createSurface(GLFWwindow* window);
    void createLogicalDevice();
    void createSwapchain();
    void createImageViews();
    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    
    // devices
    void selectPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    
    // getters
    std::vector<const char*> getRequiredExtensions();
    SwapChainSupportDetails querySwapchainSupport(VkPhysicalDevice);
    
    // chooser
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    
    // checkers
    bool checkExtensionsSupport(const std::vector<const char*> & requiredExtensions);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
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
