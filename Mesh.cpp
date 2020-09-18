#include "Mesh.hpp"

Mesh::Mesh(){}

Mesh::Mesh(VkPhysicalDevice newPhysicalDevice,
           VkDevice newDevice,
           VkQueue transferQueue,
           VkCommandPool transferCommandPool,
           const QueueFamilyIndices &queueFamilyIndices,
           const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indicies, int newTexId){
    indexCount = indicies.size();
    vertexCount = vertices.size();
    physicalDevice = newPhysicalDevice;
    device = newDevice;
    createVertexBuffer(transferQueue, transferCommandPool, queueFamilyIndices, vertices);
    createIndexBuffer(transferQueue, transferCommandPool, queueFamilyIndices, indicies);
    
    model = glm::mat4(1.0f);
    texId = newTexId;
}

Mesh::~Mesh(){}

void Mesh::destroyBuffers(){
    vkDestroyBuffer(device, indexBuffer, nullptr);
    vkFreeMemory(device, indexBufferMemory, nullptr);
    vkDestroyBuffer(device, vertexBuffer, nullptr);
    vkFreeMemory(device, vertexBufferMemory, nullptr);
}



int Mesh::getTexId(){
    return texId;
}

size_t Mesh::getIndexCount(){
    return indexCount;
}

size_t Mesh::getVertexCount(){
    return vertexCount;
}

VkBuffer Mesh::getVertexBuffer(){
    return vertexBuffer;
}

VkBuffer Mesh::getIndexBuffer(){
    return indexBuffer;
}

void Mesh::createIndexBuffer(VkQueue transferQueue,
                             VkCommandPool transferCommandPool,
                             const QueueFamilyIndices &queueFamilyIndices,
                             const std::vector<uint32_t> & indices){
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
    
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    QueueFamilyIndices ids1 = { {}, {}, queueFamilyIndices.transferFamily };
    createBuffer(device,
                 physicalDevice,
                 ids1,
                 bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingBufferMemory);
    
    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);
    
    QueueFamilyIndices ids2 = { queueFamilyIndices.graphicsFamily, {}, queueFamilyIndices.transferFamily };
    createBuffer(device,
                 physicalDevice,
                 ids2,
                 bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
    
    VkCommandBuffer commandBuffer = setUpCommandBuffer(device, transferCommandPool);
    copyBuffer(commandBuffer, stagingBuffer, indexBuffer, bufferSize);
    flushSetupCommands(device, commandBuffer, transferCommandPool, transferQueue);
    
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}

void Mesh::createVertexBuffer(VkQueue transferQueue,
                              VkCommandPool transferCommandPool,
                              const QueueFamilyIndices &queueFamilyIndices,
                              const std::vector<Vertex> &vertices){
    VkDeviceSize bufferSize = sizeof(Vertex) * vertices.size();
    
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    QueueFamilyIndices ids1 = { {}, {}, queueFamilyIndices.transferFamily };
    createBuffer(device,
                 physicalDevice,
                 ids1,
                 bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 stagingBuffer, stagingBufferMemory);
    
    void* data;
    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(device, stagingBufferMemory);
    
    QueueFamilyIndices ids2 = { queueFamilyIndices.graphicsFamily, {}, queueFamilyIndices.transferFamily };
    createBuffer(device,
                 physicalDevice,
                 ids2,
                 bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
    
    VkCommandBuffer commandBuffer = setUpCommandBuffer(device, transferCommandPool);
    copyBuffer(commandBuffer, stagingBuffer, vertexBuffer, bufferSize);
    flushSetupCommands(device, commandBuffer, transferCommandPool, transferQueue);
    
    vkDestroyBuffer(device, stagingBuffer, nullptr);
    vkFreeMemory(device, stagingBufferMemory, nullptr);
}


void Mesh::setModel(glm::mat4 newModel){
    model = newModel;
}

glm::mat4 Mesh::getModel(){
    return model;
}
