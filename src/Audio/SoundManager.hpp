#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_mixer.h>

class SoundManager {
private:
    std::unordered_map<std::string, Mix_Chunk*> soundEffects;
    Mix_Music* backgroundMusic;
    bool isInitialized;

public:
    SoundManager() : backgroundMusic(nullptr), isInitialized(false) {
        // Ініціалізація аудіо підсистеми SDL_mixer
        if (Mix_OpenAudio(44105, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
            isInitialized = false;
        } else {
            isInitialized = true;
            std::cout << "Sound Manager initialized successfully!" << std::endl;
        }
    }

    ~SoundManager() {
        for (auto& pair : soundEffects) {
            Mix_FreeChunk(pair.second);
        }
        soundEffects.clear();
        if (backgroundMusic) {
            Mix_FreeMusic(backgroundMusic);
        }
        Mix_Quit();
    }

    // Завантаження звукового ефекту (.wav)
    void loadSound(const std::string& name, const std::string& filepath) {
        if (!isInitialized) return;
        Mix_Chunk* chunk = Mix_LoadWAV(filepath.c_str());
        if (!chunk) {
            std::cout << "Failed to load sound effect! Path: " << filepath << " Error: " << Mix_GetError() << std::endl;
            return;
        }
        soundEffects[name] = chunk;
    }

    // Відтворення звукового ефекту (наприклад, зламали блок)
    void playSound(const std::string& name) {
        if (!isInitialized) return;
        auto it = soundEffects.find(name);
        if (it != soundEffects.end() && it->second) {
            Mix_PlayChannel(-1, it->second, 0);
        }
    }

    // Завантаження та запуск фонової музики (.ogg / .mp3)
    void playMusic(const std::string& filepath) {
        if (!isInitialized) return;
        backgroundMusic = Mix_LoadMUS(filepath.c_str());
        if (!backgroundMusic) {
            std::cout << "Failed to load background music! Error: " << Mix_GetError() << std::endl;
            return;
        }
        Mix_PlayMusic(backgroundMusic, -1); // -1 означає зациклене відтворення
    }
};
