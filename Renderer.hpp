#ifndef Renderer_hpp
#define Renderer_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include <vulkan/vulkan.hpp>

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
    vk::UniqueInstance instance;
    
    void createInstance();
    
    std::vector<const char*> getRequiredExtensions();
    
    bool checkExtensionsSupport(const std::vector<const char*> & requiredExtensions);
    bool checkValidationLayerSupport();
};

#endif /* Renderer_hpp */
