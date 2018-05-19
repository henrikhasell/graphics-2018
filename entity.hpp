#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ode/ode.h>
#include "model.hpp"

class Entity
{
public:
    Entity();
    virtual void move(const glm::vec2 &target){};
    virtual void step();
    glm::mat4 matrix() const;

    std::string name;
    glm::vec3 position;
    glm::quat rotation;
    Model *model;
};

class CommandEntity : public Entity
{
public:
    CommandEntity(float speed = 1.0f);
    virtual void move(const glm::vec3 &target);
    virtual void step();
private:
    glm::vec3 target;
    float speed;
};

#endif