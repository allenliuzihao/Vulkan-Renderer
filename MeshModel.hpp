#ifndef Model_hpp
#define Model_hpp

#pragma once

#include <glm/glm.hpp>

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
    
    static std::vector<std::string> LoadMaterials();
    static std::vector<Mesh> LoadNode();
    static Mesh LoadMesh();
    
    ~MeshModel();
    
private:
    std::vector<Mesh> meshList;
    glm::mat4 model;
};

#endif /* Model_hpp */
