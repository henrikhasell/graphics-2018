#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "camera.hpp"
#include "entity.hpp"
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

            for(float i = 0; i < M_PI * 2.0f; i += M_PI / 4.0f)
            {
                constexpr float radius = 8.0f;

                const float x = sinf(i) * radius;
                const float z = cosf(i) * radius;

                Entity entity;

                entity.position = glm::vec3(x, 1.0f, z);
                entity.rotation = glm::quat();
                entity.model = &cube;

                entities.push_back(entity);

            }

            Entity fe;

            fe.position = glm::vec3();
            fe.rotation = glm::quat();
            fe.model = &floor;

            entities.push_back(fe);

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
    }
private:
    Renderer renderer;
    Model cube;
    Model floor;
    Camera camera;
    std::vector<Entity> entities;
};

#endif
