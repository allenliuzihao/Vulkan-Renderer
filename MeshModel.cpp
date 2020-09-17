#include "MeshModel.hpp"

MeshModel::MeshModel(std::vector<Mesh> newMeshList){
    model = glm::mat4(1.0f);
    meshList = newMeshList;
}

MeshModel::~MeshModel(){}

size_t MeshModel::getMeshCount(){
    return meshList.size();
}

Mesh* MeshModel::getMesh(size_t index){
    if(index >= meshList.size()){
        throw std::runtime_error("attempted to access invalid mesh index.");
    }
    return &meshList[index];
}

glm::mat4 MeshModel::getModel(){
    return model;
}

void MeshModel::setModel(glm::mat4 newModel){
    model = newModel;
}

void MeshModel::destroyMeshModel(){
    for(auto &mesh: meshList){
        mesh.destroyBuffers();
    }
}

std::vector<std::string> MeshModel::LoadMaterials(){
    return { "Textures/texture.jpg" };
}

Mesh MeshModel::LoadMesh(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice,
                         VkQueue transferQueue, VkCommandPool transferCommandPool,
                         const QueueFamilyIndices &queueFamilyIndices,
                         const std::vector<int> &matToTex){
    std::vector<Vertex> v = vertices;
    std::vector<uint32_t> i = indices;
    
    return Mesh(newPhysicalDevice, newDevice, transferQueue, transferCommandPool, queueFamilyIndices, v, i, matToTex[0]);
}

std::vector<Mesh> MeshModel::LoadMeshes(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice,
                                       VkQueue transferQueue, VkCommandPool transferCommandPool,
                                       const QueueFamilyIndices & queueFamilyIndices,
                                       const std::vector<int> &matToTex){
    return { LoadMesh(newPhysicalDevice, newDevice, transferQueue, transferCommandPool, queueFamilyIndices, matToTex) };
}

void MeshModel::updateModel(){
    static auto startTime = std::chrono::high_resolution_clock::now();
    
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();       // in seconds
        
    model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
}
