#include "entity.hpp"
#include <iostream>

Entity::Entity() :
    position(0, 0, 0),
    rotation(0, 0, 0, 1),
    physics(nullptr),
    model(nullptr)
{

}

glm::mat4 Entity::matrix() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation);
}

void Entity::step()
{
    if(physics)
    {
        const dReal *pos = dBodyGetPosition(physics);
        const dReal *rot = dBodyGetQuaternion(physics);

        position = glm::vec3(pos[0], pos[1], pos[2]);
        rotation = glm::quat(rot[0], rot[1], rot[2], rot[3]);
    }
}

CommandEntity::CommandEntity(float speed) :
    commandEntityState(Idle),
    target(position),
    speed(speed)
{

}

void CommandEntity::move(const glm::vec3 &target)
{
    this->target = glm::vec3(target.x, 1.0f, target.z);
    commandEntityState = Moving;
}

void CommandEntity::step()
{
    if(commandEntityState == Moving)
    {
        const glm::vec3 difference = target - position;
        const float a2 = difference.x * difference.x;
        const float b2 = difference.z * difference.z;
        const float distance = sqrtf(a2 + b2);

        if(distance < speed * 0.5f)
        {
            if(physics)
            {
                dBodySetPosition(physics, target.x, target.y, target.z);
                dBodySetLinearVel(physics, 0.0f, 0.0f, 0.0f);
            }
            else
            {
                position = target;
            }

            commandEntityState = Idle;
        }
        else
        {
            glm::vec3 velocity = glm::normalize(difference) * speed;

            if(physics)
            {
                dBodyEnable(physics);
                velocity *= (1000/60);

                dBodySetLinearVel(physics, velocity.x, velocity.y, velocity.z);
            }
            else
            {
                position += velocity;
            }
        }
    }

    if(physics)
    {
        const dReal identityQuaternion[4] =
        {
            0.0f, 0.0f, 0.0f, 1.0f
        };
        dBodySetAngularVel(physics, 0.0f, 0.0f, 0.0f);
        dBodySetQuaternion(physics,identityQuaternion);
    }

    Entity::step();
}