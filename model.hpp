#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <utility>
#include <assimp/scene.h>
#include "material.hpp"
#include "mesh.hpp"

class Model
{
    friend class Renderer;
    friend class ShadowMap;
public:
    bool load(const char path[]);
    bool load(const char path[], const aiScene *scene);
private:
    std::vector<Material> materials;
    std::vector<std::pair<size_t, Mesh>> meshes;
};

#endif