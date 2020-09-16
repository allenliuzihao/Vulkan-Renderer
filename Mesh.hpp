#ifndef Mesh_hpp
#define Mesh_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Utilities.h"

struct Model {
    glm::mat4 model;
};

class Mesh{
public:
    Mesh();
    Mesh(VkPhysicalDevice newPhysicalDevice,
         VkDevice newDevice,
         VkQueue transferQueue,
         VkCommandPool transferCommandPool,
         std::vector<Vertex>* vertices, std::vector<uint32_t>* indicies, int newTexId);
    
    void setModel(glm::mat4 newModel);
    Model getModel();
    
    int getTexId();
    
    size_t getVertexCount();
    size_t getIndexCount();

    VkBuffer getVertexBuffer();
    VkBuffer getIndexBuffer();

    void destroyBuffers();
    
    ~Mesh();
private:
    Model model;
    
    int texId;
    
    size_t vertexCount;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    
    size_t indexCount;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    
    void createVertexBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<Vertex> *vertices);
    void createIndexBuffer(VkQueue transferQueue, VkCommandPool transferCommandPool, std::vector<uint32_t> *indices);
};

#endif /* Mesh_hpp */
