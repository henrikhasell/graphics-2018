#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
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
    virtual void move(const glm::vec3 &target){std::cout << "Base move." << std::endl;};
    virtual void step();
    glm::mat4 matrix() const;

    std::string name;
    glm::vec3 position;
    glm::quat rotation;
    dBodyID physics;
    Model *model;
};

enum CommandEntityState
{
    Idle,
    Moving
};

class CommandEntity : public Entity
{
public:
    CommandEntityState commandEntityState;
    CommandEntity(float speed = 1.0f);
    virtual void move(const glm::vec3 &target);
    virtual void step();
    glm::vec3 target;
private:
    float speed;
};

#endif