#ifndef Renderer_hpp
#define Renderer_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
#include "Mesh.hpp"
#include "MeshModel.hpp"

class Renderer{
public:
    void init(GLFWwindow* window);
    void cleanUp();
    void draw();
    void setFramebufferResized(bool resized);
    
    int createMeshModel(std::string modelFile);
    void updateModel(int modelId);
    
private:    
    // window
    GLFWwindow* wd;
    bool framebufferResized = false;
    
    // model
    std::vector<MeshModel> modelList;
    
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
    VkDescriptorSetLayout samplerSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPushConstantRange pushConstantRange;
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
    
    // images and textures
    uint32_t mipLevels;
    std::vector<VkImage> textureImages;
    std::vector<VkDeviceMemory> textureImagesMemory;
    std::vector<VkImageView> textureImageViews;
    VkSampler textureSampler;
    
    // UBO
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    
    // descriptors and push constants
    VkDescriptorPool descriptorPool;
    VkDescriptorPool samplerDescriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<VkDescriptorSet> samplerDescriptorSets;
    
    // MSAA
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;
    
    // depth buffer
    VkImage depthBufferImage;
    VkDeviceMemory depthBufferImageMemory;
    VkImageView depthBufferImageView;
    
    // Note: only one color and one depth buffer are needed due to the availability of one graphics pipeline
    // despite the fact that multiple frames are inflight. The drawing operations in the pipeline is one frame at the time so
    // these buffers can be shared amongst multiple inflight frames no problem.
    
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
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSynchronizations();
    void createDepthBuffer();
    void createTextureSampler();
    void createSamplerDescriptorPool();
    void createColorBuffer();
    
    int createTextureDescriptor(VkImageView textureImage);
    int createTextureImage(std::string fileName);
    int createTexture(std::string fileName);
    
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
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
    VkFormat findDepthFormat();
    
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
