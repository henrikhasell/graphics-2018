#include <iostream>
#include <ode/ode.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "application.hpp"

#define WINDOW_TITLE "Example OpenGL Context"
#define WINDOW_W 800
#define WINDOW_H 600

#define IMG_INIT_FLAGS (IMG_INIT_PNG | IMG_INIT_JPG)

int main(int argc, char *argv[])
{
    SDL_version version;

    SDL_GetVersion(&version);

    std::cout << "Linked against SDL version " <<
        (int)version.major << "." <<
        (int)version.minor << "." <<
        (int)version.patch << std::endl;

    const SDL_version *img_version = IMG_Linked_Version();

    std::cout << "Linked against SDL_image version " <<
        (int)img_version->major << "." <<
        (int)img_version->minor << "." <<
        (int)img_version->patch << std::endl;

    const SDL_version *ttf_version = IMG_Linked_Version();

    std::cout << "Linked against SDL_ttf version " <<
              (int)ttf_version->major << "." <<
              (int)ttf_version->minor << "." <<
              (int)ttf_version->patch << std::endl;

    SDL_Window *window = nullptr;
    SDL_GLContext context;

    if(SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        if(IMG_Init(IMG_INIT_FLAGS) == IMG_INIT_FLAGS)
        {
            if(TTF_Init() == 0)
            {
                window = SDL_CreateWindow(
                        WINDOW_TITLE,
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        WINDOW_W,
                        WINDOW_H,
                        SDL_WINDOW_OPENGL);

                if(window != nullptr)
                {
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
                    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
                    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

                    context = SDL_GL_CreateContext(window);

                    if(context != nullptr)
                    {
                        GLenum glewStatus = glewInit();

                        if(glewStatus == GLEW_OK)
                        {
                            glEnable(GL_DEPTH_TEST);
                            //glEnable(GL_CULL_FACE);
                            glEnable(GL_BLEND);
                            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                            if(dInitODE2(0))
                            {
                                bool finished = false;
                                Application *application = new BumpApplication();
                                const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

                                while(!finished)
                                {
                                    SDL_Event event;

                                    while(SDL_PollEvent(&event) != 0)
                                    {
                                        if(event.type == SDL_QUIT)
                                        {
                                            finished = true;
                                            break;
                                        }
                                        else
                                        {
                                            application->handleEvent(event);
                                        }
                                    }

                                    application->work(keyboardState);
                                    application->renderScene(window);

                                    SDL_Delay(20);
                                }

                                delete application;
                                dCloseODE();
                            }

                            SDL_GL_DeleteContext(context);
                        }
                        else
                        {
                            std::cerr << "glewInit: " << glewGetErrorString(glewStatus) << std::endl;
                        }
                    }
                    else
                    {
                        std::cerr << "SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
                    }

                    SDL_DestroyWindow(window);
                }
                else
                {
                    std::cerr << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
                }
                TTF_Quit();
            }
            else
            {
                std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
            }
            IMG_Quit();
        }
        else
        {
            std::cerr << "IMG_Init: " << IMG_GetError() << std::endl;
        }
        SDL_Quit();
    }
    else
    {
        std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
    }

    return EXIT_SUCCESS;
}
