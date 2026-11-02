#pragma once
#include <SDL.h>
#include <iostream>

class Platform {
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    bool running;

public:
    Platform(const char* title, int width, int height) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
            std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
            exit(-1);
        }

        // Старий OpenGL 2.1 для ПК або OpenGL ES 2.0 для телефонів (Android/iOS)
        #if defined(__ANDROID__) || defined(__IPHONEOS__)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        #else
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        #endif

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!window) {
            std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
            SDL_Quit();
            exit(-1);
        }

        glContext = SDL_GL_CreateContext(window);
        SDL_GL_SetSwapInterval(1); // VSync
        running = true;
        std::cout << "Platform Initialized Successfully!" << std::endl;
    }

    ~Platform() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool isRunning() const { return running; }

    void quit() { running = false; }

    void swapBuffers() {
        SDL_GL_SwapWindow(window);
    }
};
