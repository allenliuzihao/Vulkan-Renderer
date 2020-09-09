#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <stdexcept>
#include <iostream>

#include "Utilities.h"
#include "Renderer.hpp"

Renderer renderer;

int main() {
    
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    
    renderer.init();
    
    while(!glfwWindowShouldClose(window)) {
     glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    renderer.cleanUp();
    
    return 0;
}
