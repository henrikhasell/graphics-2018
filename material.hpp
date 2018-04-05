#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "texture.hpp"

struct Material
{
    Material() :
        ambient(1, 1, 1),
        diffuse(1, 0, 0),
        specular(1, 1, 1),
        normal(0.5, 0.5, 1.0)
    {

    }

    void bind() const
    {
        ambient.bind(GL_TEXTURE0);
        diffuse.bind(GL_TEXTURE1);
        specular.bind(GL_TEXTURE2);
        normal.bind(GL_TEXTURE3);
    }

    Texture ambient;
    Texture diffuse;
    Texture specular;

    Texture normal;
};
#endif