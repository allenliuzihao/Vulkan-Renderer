#ifndef Utilities_h
#define Utilities_h

#pragma once

#include <stdexcept>
#include <vector>
#include <optional>
#include <fstream>

const int MAX_FRAMES_IN_FLIGHT = 2;

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete(){
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    
    bool isAdequate(){
        return !formats.empty() && !presentModes.empty();
    }
};

static inline std::vector<char> readFile(const std::string & filename){
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    
    if(!file.is_open()){
        throw std::runtime_error(std::string("failed to open file: ") + filename + " with error: " +  strerror(errno));
    }
    
    size_t fileSize = (size_t) file.tellg();
    
    
    std::vector<char> buffer(fileSize);
    
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    
    return buffer;
}

#endif /* Utilities_h */
