#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Platform.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"
#include "World/World.hpp"
#include "Render/Shader.hpp"
#include "Render/Renderer.hpp"
#include "Render/TextureLoader.hpp"

int main(int argc, char* argv[]) {
    std::cout << "=== INITIALIZING FINAL LUANTI-STYLE NATIVE ENGINE ===" << std::endl;

    Platform platform("Voxel Engine - Standalone 3D", 1280, 720);
    Input input;
    Camera camera(glm::vec3(8.0f, 15.0f, 25.0f));

    World world;
    // Генеруємо сітку чанків 3х3 навколо старту
    world.loadChunksAroundPlayer(0, 0, 1);

    Shader shader(voxelVertexShaderSrc, voxelFragmentShaderSrc);
    GLuint grassTexture = TextureLoader::loadTexturePNG("assets/textures/blocks/grass_top.png");

    bool isRunning = true;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Вмикаємо відсікання задніх стінок для максимального FPS
    glCullFace(GL_BACK);

    while (isRunning) {
        input.handleEvents(isRunning);

        // Рух гравця (WASD)
        if (input.isKeyPressed(SDL_SCANCODE_W)) camera.processKeyboard('W', 0.016f);
        if (input.isKeyPressed(SDL_SCANCODE_S)) camera.processKeyboard('S', 0.016f);
        if (input.isKeyPressed(SDL_SCANCODE_A)) camera.processKeyboard('A', 0.016f);
        if (input.isKeyPressed(SDL_SCANCODE_D)) camera.processKeyboard('D', 0.016f);

        // Очищення екрана кольором неба
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Розрахунок матриць камери (Вигляд + Проєкція)
        glm::mat4 projection = glm::perspective(glm::radians(75.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 mvp = projection * view;

        shader.use();
        shader.setMat4("uMVP", &mvp[0][0]);

        // Рендеримо весь згенерований світ
        Renderer::renderWorld(world, shader, grassTexture);

        platform.swapBuffers();
    }

    std::cout << "Engine shut down cleanly." << std::endl;
    return 0;
}
