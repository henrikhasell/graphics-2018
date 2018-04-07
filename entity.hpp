#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include "model.hpp"

struct Entity
{
    glm::vec3 position;
    glm::quat rotation;
    Model *model;
};

#endif