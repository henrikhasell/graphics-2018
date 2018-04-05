#include "model.hpp"
#include "path.hpp"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#define MODEL_IMPORT_FLAGS (\
    aiProcess_GenSmoothNormals |\
    aiProcess_Triangulate |\
    aiProcess_GenUVCoords |\
    aiProcess_SortByPType |\
    aiProcess_FlipUVs)

bool Model::load(const char path[])
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path, MODEL_IMPORT_FLAGS);

    if(scene)
    {
        load(path, scene);
    }
    else
    {
        std::cerr << "Failed to load " << path << std::endl;
    }

    return scene != nullptr;
}

bool Model::load(const char path[], const aiScene *scene)
{
    const std::string pathString = remove_filename(path);
    materials.resize(scene->mNumMaterials);

    for(unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        aiString string;
        aiReturn result = scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &string);

        if(result == AI_SUCCESS)
        {
            const std::string fullPath = pathString + string.data;
            materials[i].diffuse.load(fullPath.c_str());
        }

        result = scene->mMaterials[i]->GetTexture(aiTextureType_HEIGHT, 0, &string);

        if(result == AI_SUCCESS)
        {
            const std::string fullPath = pathString + string.data;
            materials[i].normal.load(fullPath.c_str());
        }
    }

    meshes.resize(scene->mNumMeshes);

    for(unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        meshes[i].first = scene->mMeshes[i]->mMaterialIndex;
        meshes[i].second.load(scene->mMeshes[i]);
    }

    return true;
}