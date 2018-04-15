#ifndef ORTHOGRAPHIC_HPP
#define ORTHOGRAPHIC_HPP

// Orthographic rendering system.

#include <GL/glew.h>
#include "program.hpp"
#include "shader.hpp"
#include "shape.hpp"
#include "sprite.hpp"

class Orthographic
{
public:
    Orthographic();
    ~Orthographic();
    bool initialise();
    void projection(float width, float height) const;
    void begin() const;
    void end() const;
    void draw(const Shape &shape) const;
    void draw(const Sprite &sprite) const;
private:
    Program program;
    Shader vertexShader;
    Shader fragmentShader;

    GLuint uniform_projectionMatrix;
    GLuint uniform_modelMatrix;
};

#endif