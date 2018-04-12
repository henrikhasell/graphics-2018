#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <glm/vec3.hpp>
#include <ode/ode.h>

#define MAX_CONTACTS 32

class Physics
{
    friend class Renderer;
    friend class ShadowMap;
public:
    static void nearCallback(void *data, dGeomID o1, dGeomID o2);
    Physics();
    ~Physics();
    void step();
    void select(const glm::vec3 &position, const glm::vec3 &direction);
    dBodyID createCube(const glm::vec3 &position);
private:
    dWorldID world;
    dSpaceID space;
    dGeomID selection;
    dGeomID plane;
    dJointGroupID contactGroup;
};

#endif