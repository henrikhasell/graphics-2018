#include "orthographic.hpp"
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

Orthographic::Orthographic() :
    vertexShader(GL_VERTEX_SHADER),
    fragmentShader(GL_FRAGMENT_SHADER)
{

}

Orthographic::~Orthographic()
{

}

bool Orthographic::initialise()
{
    bool success = vertexShader.load("shaders/ortho_vertex.glsl") && fragmentShader.load("shaders/ortho_fragment.glsl");

    if(success)
    {
        success = program.link(vertexShader, fragmentShader);

        if(success)
        {
            program.bindAttributeLocation(0, "in_Position");
            program.bindAttributeLocation(1, "in_TexCoord");

            uniform_projectionMatrix = program.getUniformLocation("projectionMatrix");
            uniform_modelMatrix = program.getUniformLocation("modelMatrix");
        }
        else
        {
            std::cerr << program.infoLog() << std::endl;
        }
    }

    return success;
}

void Orthographic::projection(float width, float height) const
{
    program.use();
    const glm::mat4 projectionMatrix = glm::ortho(0.0f, width, height, 0.0f);
    glUniformMatrix4fv(uniform_projectionMatrix, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Orthographic::begin() const
{
    program.use();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Orthographic::end() const
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Orthographic::draw(const Shape &shape) const
{
    glBindBuffer(GL_ARRAY_BUFFER, shape.vertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, shape.textureBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.indexBuffer);
    glDrawElements(GL_TRIANGLES, shape.size, GL_UNSIGNED_INT, (void*)0);
}

void Orthographic::draw(const Sprite &sprite) const
{
    if(sprite.shape)
    {
        const glm::mat4 modelMatrix = sprite.modelMatrix();
        glUniformMatrix4fv(uniform_modelMatrix, 1, GL_FALSE, &modelMatrix[0][0]);
        sprite.texture.bind();
        draw(*sprite.shape);
    }
}