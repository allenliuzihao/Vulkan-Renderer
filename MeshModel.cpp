#define TINYOBJLOADER_IMPLEMENTATION
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
    return { TEXTURE_PATH };
}

Mesh MeshModel::LoadMesh(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice,
                         VkQueue transferQueue, VkCommandPool transferCommandPool,
                         const QueueFamilyIndices &queueFamilyIndices,
                         const std::vector<int> &matToTex){
    
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
        throw std::runtime_error(warn + err);
    }
    
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};
            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };
            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                attrib.texcoords[2 * index.texcoord_index + 1]
            };
            vertex.color = {1.0f, 1.0f, 1.0f};
            
            vertices.push_back(vertex);
            indices.push_back(static_cast<uint32_t>(indices.size()));
        }
    }
    
    return Mesh(newPhysicalDevice, newDevice, transferQueue, transferCommandPool, queueFamilyIndices, vertices, indices, matToTex[0]);
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
