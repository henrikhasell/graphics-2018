#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include "texture.hpp"
#include "shape.hpp"
#include "font.hpp"

struct Sprite
{
    bool text(Font &font, const char format[]);
    glm::mat4 modelMatrix() const;

    glm::vec2 position;
    Texture texture;
    Shape shape;
};

#endif