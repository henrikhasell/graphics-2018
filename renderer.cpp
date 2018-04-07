#include "renderer.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

Renderer::Renderer() :
        vertexShader(GL_VERTEX_SHADER),
        fragmentShader(GL_FRAGMENT_SHADER)
{

}

bool Renderer::initialise()
{
    bool success = vertexShader.load("shaders/bump_vertex.glsl") && fragmentShader.load("shaders/bump_fragment.glsl");

    if(success)
    {
        success = program.link(vertexShader, fragmentShader);

        if(success)
        {
            program.bindAttributeLocation(0, "in_Position");
            program.bindAttributeLocation(1, "in_Normal");
            program.bindAttributeLocation(2, "in_Tangent");
            program.bindAttributeLocation(3, "in_Bitangent");
            program.bindAttributeLocation(4, "in_TexCoord");

            uniform_projectionMatrix = program.getUniformLocation("projectionMatrix");
            uniform_modelMatrix = program.getUniformLocation("modelMatrix");
            uniform_viewMatrix = program.getUniformLocation("viewMatrix");
            uniform_cameraNormal = program.getUniformLocation("camera_Normal");

            program.use();

            glUniform1i(program.getUniformLocation("material_Ambient"), 0);
            glUniform1i(program.getUniformLocation("material_Diffuse"), 1);
            glUniform1i(program.getUniformLocation("material_Specular"), 2);
            glUniform1i(program.getUniformLocation("material_Normal"), 3);
        }
        else
        {
            std::cerr << program.infoLog() << std::endl;
        }

    }

    return success;
}

void Renderer::projection(float width, float height) const
{
    glm::mat4 projection = glm::perspective(45.0f, width / height, 0.1f, 1000.0f);
    program.use();
    glUniformMatrix4fv(uniform_projectionMatrix, 1, GL_FALSE, &projection[0][0]);
}

void Renderer::view(const Camera &camera) const
{
    const glm::mat4 matrix = camera.matrix();
    const glm::vec3 forward = camera.forward();
    glUniformMatrix4fv(uniform_viewMatrix, 1, GL_FALSE, &matrix[0][0]);
    glUniform3fv(uniform_cameraNormal, 1, &forward[0]);
}

void Renderer::begin() const
{
    program.use();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::end() const
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
}


void Renderer::position(const glm::vec3 &position) // TODO Create transform struct.
{
    glUniformMatrix4fv(uniform_modelMatrix, 1, GL_FALSE, &glm::translate(glm::mat4(1.0f), position)[0][0]);
}

void Renderer::rotation(const glm::quat &rotation)
{
    glUniformMatrix4fv(uniform_modelMatrix, 1, GL_FALSE, &glm::toMat4(rotation)[0][0]);
}

void Renderer::draw(const Entity &entity) const
{
    if(entity.model)
    {

    }
}

void Renderer::draw(const Model &model) const
{
    for(const std::pair<size_t, Mesh> &texture_mesh_pair : model.meshes)
    {
        model.materials[texture_mesh_pair.first].bind();
        draw(texture_mesh_pair.second);
    }
}

void Renderer::draw(const Mesh &mesh) const
{
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.tangentBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.bitangentBuffer);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.texCoordBuffer);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);
    glDrawElements(GL_TRIANGLES, mesh.indices, GL_UNSIGNED_INT, (GLvoid*)0);
}