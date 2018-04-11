#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "camera.hpp"
#include "entity.hpp"
#include "physics.hpp"
#include "renderer.hpp"

#define TIME_STEP (1000/60)

class Application
{
public:
    Application()
    {
        lastTimeStep = SDL_GetTicks();
    }

    virtual ~Application() = default;

    void work(const Uint8 *keyboardState)
    {
        for(Uint32 time = SDL_GetTicks(); lastTimeStep - time > TIME_STEP; lastTimeStep += TIME_STEP)
        {
            step(keyboardState);
        }
    }
    virtual void handleEvent(const SDL_Event &event) = 0;
    virtual void renderScene(SDL_Window *window) = 0;
protected:
    virtual void step(const Uint8 *keyboardState) = 0;
private:
    Uint32 lastTimeStep;
};

class BumpApplication : public Application
{
public:
    BumpApplication()
    {
        std::cout << "Initialising bump application..." << std::endl;

        if(renderer.initialise())
        {
            renderer.projection(800, 600);
            cube.load("models/cube.obj");
            floor.load("models/floor.obj");

            for(size_t i = 0; i < 5; i++)
            {
                const float angle = i * (float)(M_PI / 2.5);
                constexpr float radius = 8.0f;

                const float x = sinf(angle) * radius;
                const float z = cosf(angle) * radius;

                Entity entity;

                entity.position = glm::vec3(x, 1.0f, z);
                entity.model = &cube;
                entity.physics = physics.createCube(glm::vec3(x, 5, z));

                entities.push_back(entity);

            }

            Entity floorEntity;
            floorEntity.position = glm::vec3();
            floorEntity.rotation = glm::quat();
            floorEntity.model = &floor;
            entities.push_back(floorEntity);

            Entity physicsEntity;
            physicsEntity.physics = physics.createCube(glm::vec3(0, 5, 0));
            physicsEntity.model = &cube;
            entities.push_back(physicsEntity);

        }
    }
    ~BumpApplication() override
    {
        std::cout << "Destroying bump application..." << std::endl;
    }
    void handleEvent(const SDL_Event &event) override
    {
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
                camera.handle(event.motion);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_LCTRL && !event.key.repeat)
                {
                    SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() ? SDL_FALSE : SDL_TRUE);
                }
                break;
        }
    }
    void renderScene(SDL_Window *window) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.begin();
        renderer.view(camera);
        for(const Entity &entity : entities)
        {
            renderer.draw(entity);
        }
        renderer.end();
        SDL_GL_SwapWindow(window);
    }
protected:
    void step(const Uint8 *keyboardState) override
    {
        camera.handle(keyboardState);
        physics.step();
        for(Entity &entity : entities)
        {
            entity.step();
        }
    }
private:
    Renderer renderer;
    Model cube;
    Model floor;
    Camera camera;
    Physics physics;
    std::vector<Entity> entities;
};

#endif
