#pragma once
#include <SDL.h>
#include <iostream>

class PlatformWindow {
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    bool running;

public:
    PlatformWindow(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        // Встановлюємо OpenGL 2.1 для максимальної сумісності зі старими ноутбуками
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        // Compatibility профіль дозволяє використовувати старі функції OpenGL (те, що треба для старих ноутів)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                  width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!window) {
            std::cerr << "Window Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }

        glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            std::cerr << "OpenGL Context Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(-1);
        }

        SDL_GL_SetSwapInterval(1); // VSync
        running = true;
        std::cout << "OpenGL Initialized Successfully (Compatible Mode for Old Laptops)!" << std::endl;
    }

    ~PlatformWindow() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool isRunning() { return running; }

    void pollEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
        }
    }

    void swapBuffers() {
        SDL_GL_SwapWindow(window);
    }
};
