#include "MeshModel.hpp"

MeshModel::MeshModel(std::vector<Mesh> newMeshList){
    meshList = newMeshList;
    model = glm::mat4(1.0f);
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
    return { TEXTURE_PATH };
}

Mesh MeshModel::LoadMesh(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice,
                         VkQueue transferQueue, VkCommandPool transferCommandPool,
                         const QueueFamilyIndices &queueFamilyIndices,
                         const std::vector<int> &matToTex){
    //std::vector<Vertex> vertices;
    //std::vector<uint32_t> indices;
    /*
     (VkPhysicalDevice physicalDevice,
     VkDevice device,
     VkQueue transferQueue,
     VkCommandPool transferCommandPool,
     const QueueFamilyIndices &indices,
     const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indicies, int newTexId)
     */
    
    std::vector<Vertex> v = vertices;
    std::vector<uint32_t> i = indices;
    
    return Mesh(newPhysicalDevice, newDevice,
                transferQueue, transferCommandPool,
                queueFamilyIndices,
                v, i, matToTex[0]);
}

