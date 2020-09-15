#ifndef Renderer_hpp
#define Renderer_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>
#include <cstdlib>
#include <cstdint> // Necessary for UINT32_MAX
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <optional>
#include <array>
#include <unordered_set>


#include "stb_image.h"

#include "Utilities.h"

class Renderer{
public:
    void init(GLFWwindow* window);
    void cleanUp();
    void draw();
    void setFramebufferResized(bool resized);
    
private:    
    // window
    GLFWwindow* wd;
    bool framebufferResized = false;

    // vulkan instance
    VkInstance instance;
    
    // GPU instance
    VkDevice device;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    
    // vulkan queues
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkQueue transferQueue;
    QueueFamilyIndices queueFamilyIndices;
    
    // surface
    VkSurfaceKHR surface;
    
    // swapchain
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    
    // render pass
    VkRenderPass renderPass;
    
    // pipeline
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    
    // commands
    VkCommandPool graphicsCommandPool;
    VkCommandPool transferCommandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    
    // synchronizations
    size_t currentFrame = 0;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    
    // buffers
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    
    // images and textures
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    
    // UBO
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    
    // descriptors and push constants
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    VkPushConstantRange pushConstantRange;
    
    // helper functions
    // creators
    void createInstance();
    void createSurface();
    void createLogicalDevice();
    void createSwapchain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    void createPushConstantRange();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSynchronizations();
    void createTextureImage();
    void createTextureImageView();
    VkImageView createImageView(VkImage image, VkFormat format);
    VkShaderModule createShaderModule(const std::vector<char>& code);

    // swapchain recreation:
    void recreateSwapchain();
    void cleanUpSwapchain();
    
    // uniform buffer
    void updateUniformBuffers();
    
    // record commands
    void recordCommands(uint32_t currentImage);
    
    // devices
    void selectPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    
    // getters
    std::vector<const char*> getRequiredExtensions();
    SwapChainSupportDetails querySwapchainSupport(VkPhysicalDevice);
    PushConstantModel getModelUpdate();

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
