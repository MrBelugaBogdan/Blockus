#include <iostream>
#include "Core/Platform.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"
#include "World/Chunk.hpp"
#include "Render/Shader.hpp"
#include "Render/TextureLoader.hpp"

int main(int argc, char* argv[]) {
    std::cout << "=== INITIALIZING FULL NATIVE VOXEL ENGINE (C++ / OpenGL) ===" << std::endl;

    Platform platform("Voxel Engine - 3D World", 1280, 720);
    Input input;
    Camera camera(glm::vec3(8.0f, 10.0f, 20.0f));

    // Створюємо генерацію чанка та завантаження текстур (під твої майбутні PNG)
    Chunk spawnChunk(0, 0);
    GLuint blockTexture = TextureLoader::loadTexturePNG("assets/textures/blocks/grass_top.png");

    bool isRunning = true;
    glEnable(GL_DEPTH_TEST);

    while (isRunning) {
        input.handleEvents(isRunning);

        // Перевірка клавіш керування WASD для камери
        if (input.isKeyPressed(SDL_SCANCODE_W)) camera.processKeyboard('W', 0.016f);
        if (input.isKeyPressed(SDL_SCANCODE_S)) camera.processKeyboard('S', 0.016f);
        if (input.isKeyPressed(SDL_SCANCODE_W)) camera.processKeyboard('A', 0.016f);
        if (input.isKeyPressed(SDL_SCANCODE_D)) camera.processKeyboard('D', 0.016f);

        // Очищення екрана
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Тут у наступному кроці ми передаватимемо матрицю камери у шейдер для рендерингу всього світу

        platform.swapBuffers();
    }

    std::cout << "Engine closed." << std::endl;
    return 0;
}
