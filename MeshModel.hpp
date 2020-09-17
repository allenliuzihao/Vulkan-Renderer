#ifndef Model_hpp
#define Model_hpp

#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tiny_obj_loader.h"

#include "Mesh.hpp"

class MeshModel {
public:
    MeshModel();
    MeshModel(std::vector<Mesh> newMeshList);
    
    size_t getMeshCount();
    Mesh* getMesh(size_t index);
    
    glm::mat4 getModel();
    void setModel(glm::mat4 newModel);
    
    void destroyMeshModel();
    
    void updateModel();
    
    static std::vector<std::string> LoadMaterials();
    static Mesh LoadMesh(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice,
                         VkQueue transferQueue, VkCommandPool transferCommandPool,
                         const QueueFamilyIndices & queueFamilyIndices,
                         const std::vector<int> &matToTex);
    static std::vector<Mesh> LoadMeshes(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice,
                                        VkQueue transferQueue, VkCommandPool transferCommandPool,
                                        const QueueFamilyIndices & queueFamilyIndices,
                                        const std::vector<int> &matToTex);
    ~MeshModel();
    
private:
    std::vector<Mesh> meshList;
    glm::mat4 model;
};

#endif /* Model_hpp */
