#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ode/ode.h>
#include "model.hpp"

struct Entity
{
    glm::vec3 position;
    glm::quat rotation;
    dBodyID physics;
    Model *model;

    Entity() :
        position(0, 0, 0),
        rotation(0, 0, 0, 1),
        physics(nullptr),
        model(nullptr)
    {

    }

    glm::mat4 matrix() const
    {
        return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation);
    }

    void step()
    {
        if(physics)
        {
            const dReal *pos = dBodyGetPosition(physics);
            const dReal *rot = dBodyGetQuaternion(physics);

            position = glm::vec3(pos[0], pos[1], pos[2]);
            rotation = glm::quat(rot[0], rot[1], rot[2], rot[3]);
        }
    }
};

#endif