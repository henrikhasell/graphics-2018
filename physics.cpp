#include "physics.hpp"

Physics::Physics()
{
    world = dWorldCreate();
    space = dHashSpaceCreate(0);
    contactGroup = dJointGroupCreate(0);

    dWorldSetGravity(world, 0.0f, -9.8f, 0.0f);
    dWorldSetCFM(world, 1e-5f);
    dWorldSetAutoDisableFlag(world, 1);

    dCreatePlane(space, 0.0f, 1.0f, 0.0f, 0.0f);
}

Physics::~Physics()
{
    dJointGroupDestroy(contactGroup);
    dSpaceDestroy(space);
    dWorldDestroy(world);
}

void Physics::nearCallback(void *data, dGeomID o1, dGeomID o2)
{
    Physics *instance = (Physics*)data; // Wacky.

    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);

    dContact contact[MAX_CONTACTS];

    for(int i = 0; i < MAX_CONTACTS; i++)
    {
        contact[i].surface.mode = dContactBounce;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 0;
        contact[i].surface.bounce = 0.2f;
        contact[i].surface.bounce_vel = 0.1f;
        contact[i].surface.soft_cfm = 0.0f;
    }

    int number_collisions = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact));

    for(int i = 0; i < number_collisions; i++)
    {
        dJointID c = dJointCreateContact(instance->world, instance->contactGroup, contact + i);
        dJointAttach(c, b1, b2);
    }
}

void Physics::step()
{
    dSpaceCollide(space, this, &nearCallback);
    dWorldQuickStep(world, 1.0f/60.0f);
    dJointGroupEmpty(contactGroup);
}

dBodyID Physics::createCube(const glm::vec3 &position)
{
    dGeomID geometry = dCreateBox(space, 2.0f, 2.0f, 2.0f);
    dBodyID cube = dBodyCreate(world);
    dMass mass;

    dMassSetBox(&mass, 1.0f, 1.0f, 1.0f, 1.0f);
    dBodySetMass(cube, &mass);
    dGeomSetBody(geometry, cube);
    dBodySetPosition(cube, position.x, position.y, position.z);

    return cube;
}