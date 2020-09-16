#ifndef Mesh_hpp
#define Mesh_hpp

#pragma once

#define GLFW_INCLUDE_VULKAN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "Utilities.h"

class Mesh{
public:
    Mesh();
    Mesh(VkPhysicalDevice physicalDevice,
         VkDevice device,
         VkQueue transferQueue,
         VkCommandPool transferCommandPool,
         const QueueFamilyIndices &indices,
         const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indicies, int newTexId);
    
    void setModel(glm::mat4 newModel);
    glm::mat4 getModel();
    
    int getTexId();
    
    size_t getVertexCount();
    size_t getIndexCount();

    VkBuffer getVertexBuffer();
    VkBuffer getIndexBuffer();

    void destroyBuffers();
    
    ~Mesh();
private:
    glm::mat4 model;
    
    int texId;
    
    size_t vertexCount;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    
    size_t indexCount;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    
    void createVertexBuffer(VkQueue transferQueue,
                            VkCommandPool transferCommandPool,
                            const QueueFamilyIndices &queueFamilyIndices,
                            const std::vector<Vertex> &vertices);
    void createIndexBuffer(VkQueue transferQueue,
                           VkCommandPool transferCommandPool,
                           const QueueFamilyIndices &queueFamilyIndices,
                           const std::vector<uint32_t> &indices);
};

#endif /* Mesh_hpp */
