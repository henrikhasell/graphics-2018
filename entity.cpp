#include "entity.hpp"

Entity::Entity() :
    position(0, 0, 0),
    rotation(0, 0, 0, 1),
    model(nullptr)
{

}

glm::mat4 Entity::matrix() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation);
}

void Entity::step()
{

}

CommandEntity::CommandEntity(float speed) :
    target(position), speed(speed)
{

}

void CommandEntity::move(const glm::vec3 &target)
{
    this->target = target;
}

void CommandEntity::step()
{
    const glm::vec3 difference = target - position;
    const float a2 = difference.x * difference.x;
    const float b2 = difference.z * difference.z;
    const float distance = sqrtf(a2 + b2);

    if(distance < speed)
    {
        position = target;
    }
    else
    {
        position += glm::normalize(difference) * speed;
    }
}