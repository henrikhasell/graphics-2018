#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "model.hpp"

struct Entity
{
    glm::vec3 position;
    glm::quat rotation;

    glm::mat4 matrix() const
    {
        return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation);
    }

    Model *model;
};

#endif