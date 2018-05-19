#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <list>
#include <vector>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "camera.hpp"
#include "entity.hpp"
#include "font.hpp"
#include "physics.hpp"
#include "orthographic.hpp"
#include "renderer.hpp"

#define TIME_STEP (1000/60)

struct Selection
{
    Selection() : a(0, 0), b(0, 0)
    {
        fillSprite.texture.colour(
            0.3f,
            0.3f,
            1.0f,
            0.2f);

        lineSprite.texture.colour(
            0.3f,
            0.3f,
            1.0f);
    }

    void handle(const SDL_MouseButtonEvent &event)
    {
        if(event.button == SDL_BUTTON_LEFT)
        {
            if(event.state == SDL_PRESSED)
            {
                a = b = glm::vec2(event.x, event.y);
            }
            else
            {
                a = b = glm::vec2(0, 0);
            }
        }
        updateSprite();
    }

    void handle(const SDL_MouseMotionEvent &event)
    {
        if(!SDL_GetRelativeMouseMode() && event.state & SDL_BUTTON_LMASK)
        {
            b = glm::vec2(event.x, event.y);
            updateSprite();
        }
    }

    void selectEntities(const Camera &camera, const std::vector<Entity*> &entities)
    {
        selected.clear();

        const glm::vec2 min(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y);
        const glm::vec2 max(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y);

        for(Entity *entity : entities)
        {
            glm::vec2 projection = camera.project(entity->position, glm::vec4(0, 0, 800, 600));

            if(projection.x < min.x || projection.x > max.x)
            {
                continue;
            }

            if(projection.y < min.y || projection.y > max.y)
            {
                continue;
            }

            selected.push_back(entity);
        }

        for(const Entity *entity : selected)
        {
            std::cout << "Selected " << entity->name << std::endl;
        }
    }

    void updateSprite()
    {
        const glm::vec2 min(a.x < b.x ? a.x : b.x, a.y < b.y ? a.y : b.y);
        const glm::vec2 max(a.x > b.x ? a.x : b.x, a.y > b.y ? a.y : b.y);

        const GLfloat w = max.x - min.x;
        const GLfloat h = max.y - min.y;

        fillSprite.shape.square(min.x, min.y, w, h);
        lineSprite.shape.outline(min.x, min.y, w, h);
    }

    Sprite fillSprite;
    Sprite lineSprite;

    glm::vec2 a;
    glm::vec2 b;

    std::list<Entity*> selected;
};

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

        if(orthographic.initialise() && renderer.initialise())
        {
            orthographic.projection(800, 600);
            renderer.projection(800, 600);

            iconSprite.shape.square(-4, -4, 8, 8);
            iconSprite.texture.load("images/icon.png");
            cube.load("models/cube.obj");
            floor.load("models/floor.obj");
            largeFont.load("fonts/NanumGothic-Regular.ttf", 22);
            smallFont.load("fonts/NanumGothic-Regular.ttf", 12);

            for(size_t i = 0; i < 6; i++)
            {
                const float angle = i * (float)(M_PI / 3.0);
                constexpr float radius = 8.0f;

                const float x = sinf(angle) * radius;
                const float z = cosf(angle) * radius;

                CommandEntity *entity = new CommandEntity();

                switch(i)
                {
                    case 0: entity->name = "Alpha";
                        break;
                    case 1: entity->name = "Bravo";
                        break;
                    case 2: entity->name = "Charlie";
                        break;
                    case 3: entity->name = "Delta";
                        break;
                    case 4: entity->name = "Echo";
                        break;
                    case 5: entity->name = "Foxtrot";
                        break;
                }

                entity->target = entity->position = glm::vec3(x, 1.0f, z);
                entity->model = &cube;

                entities.push_back(entity);
            }

            Entity *floorEntity = new Entity();
            floorEntity->position = glm::vec3();
            floorEntity->rotation = glm::quat();
            floorEntity->model = &floor;
            entities.push_back(floorEntity);

            Entity *middleEntity = new Entity();
            middleEntity->position = glm::vec3(0.0f, 1.0f, 0.0f);
            middleEntity->name = "Middle";
            middleEntity->model = &cube;
            entities.push_back(middleEntity);

            sprite.text(largeFont, "Hello, world!");
            sprite.position.x = 0;
            sprite.position.y = 0;

        }
    }
    ~BumpApplication() override
    {
        for(const Entity *entity : entities)
        {
            delete entity;
        }
        std::cout << "Destroying bump application..." << std::endl;
    }
    void handleEvent(const SDL_Event &event) override
    {
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                selection.handle(event.button);
                physics.select(
                    camera.unProject(
                        glm::vec2(
                            event.button.x,
                            600 - event.button.y),
                        glm::vec4(0.0f, 0.0f, 800.0f, 600.0f)
                    ),
                    camera
                );
                break;
            case SDL_MOUSEBUTTONUP:
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        selection.selectEntities(camera, entities); break;
                    case SDL_BUTTON_RIGHT:
                    {
                        const glm::vec3 target = physics.rayCollide();

                        for(Entity *entity : selection.selected)
                        {
                            entity->move(target);
                        }
                    }
                }
                selection.handle(event.button);
                break;
            case SDL_MOUSEMOTION:
                handleEvent(event.motion);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_LCTRL && !event.key.repeat)
                {
                    SDL_SetRelativeMouseMode(SDL_GetRelativeMouseMode() ? SDL_FALSE : SDL_TRUE);
                }
                break;
        }
    }
    void handleEvent(const SDL_MouseMotionEvent &event)
    {
        selection.handle(event);
        camera.handle(event);
    }
    void renderScene(SDL_Window *window) override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.begin();
        renderer.view(camera);
        for(const Entity *entity : entities)
        {
            renderer.draw(*entity);
        }
        renderer.end();
        orthographic.begin();
        orthographic.draw(sprite);
        for(const Entity *entity : entities)
        {
            const glm::vec2 position = camera.project(entity->position, glm::vec4(0.0f, 0.0f, 800.0f, 600.0f));

            Sprite textSprite;
            textSprite.text(smallFont, entity->name.c_str());

            textSprite.position = position;
            textSprite.position.x -= textSprite.texture.getW() / 2;
            textSprite.position.y -= textSprite.texture.getH() / 2 + 16.0f;

            orthographic.draw(textSprite);

            iconSprite.position = position;
            orthographic.draw(iconSprite);
        }
        orthographic.draw(selection.fillSprite);
        orthographic.draw(selection.lineSprite);
        orthographic.end();
        SDL_GL_SwapWindow(window);
    }
protected:
    void step(const Uint8 *keyboardState) override
    {
        int x;
        int y;
        SDL_GetMouseState(&x, &y);

        camera.handle(keyboardState);
        physics.step();
        for(Entity *entity : entities)
        {
            entity->step();
        }
    }
private:
    Orthographic orthographic;
    Renderer renderer;
    Sprite iconSprite;
    Sprite sprite;
    Model cube;
    Model floor;
    Font largeFont;
    Font smallFont;
    Camera camera;
    Physics physics;
    std::vector<Entity*> entities;
    Selection selection;
};

#endif
