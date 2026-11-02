#pragma once
#include <SDL.h>

class Input {
public:
    bool isKeyPressed(SDL_Scancode scancode) {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        return state[scancode];
    }

    void handleEvents(bool& running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        running = false;
                    }
                    break;
                case SDL_FINGERDOWN:
                    // Обробка натискання пальцем на екрані телефона (Android/iOS)
                    // event.tfinger.x та event.tfinger.y містять координати дотику
                    break;
            }
        }
    }
};
