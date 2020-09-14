#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <stdexcept>
#include <iostream>

#include "Utilities.h"
#include "Renderer.hpp"

Renderer renderer;

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(window));
    app->setFramebufferResized(true);
}

int main() {
    
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    
    renderer.init(window);
    
    glfwSetWindowUserPointer(window, &renderer);
    
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

        renderer.draw();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    renderer.cleanUp();
    
    return 0;
}
