#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"

struct Material
{
    Material() : specular(1, 1, 1), ambient(0, 0, 0), diffuse(1, 0, 0)
    {

    }

    void bind() const
    {
        ambient.bind(GL_TEXTURE0);

        diffuse.bind(GL_TEXTURE1);

        specular.bind(GL_TEXTURE2);
    }

    Texture ambient;
    Texture diffuse;
    Texture specular;
};
#endif