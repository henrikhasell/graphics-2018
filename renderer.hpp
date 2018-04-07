#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "camera.hpp"
#include "entity.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "program.hpp"
#include "shader.hpp"

class Renderer
{
public:
    Renderer();
    bool initialise();
    void projection(float width, float height) const;
    void view(const Camera &camera) const;
    void begin() const;
    void end() const;
    void position(const glm::vec3 &position);
    void rotation(const glm::quat &rotation);
    void draw(const Entity &entity) const;
    void draw(const Model &model) const;
    void draw(const Mesh &mesh) const;
private:
    Program program;
    Shader vertexShader;
    Shader fragmentShader;

    GLuint uniform_projectionMatrix;
    GLuint uniform_modelMatrix;
    GLuint uniform_viewMatrix;
    GLuint uniform_cameraNormal;
};

#endif