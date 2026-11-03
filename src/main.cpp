#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Platform.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"
#include "Core/Player.hpp"
#include "World/World.hpp"
#include "World/Raycast.hpp"
#include "Render/Shader.hpp"
#include "Render/Renderer.hpp"
#include "Render/TextureLoader.hpp"

// Шейдери для OpenGL 2.1 / ES 2.0
const char* voxelVertexShaderSrc = 
    "attribute vec3 aPos;\n"
    "attribute vec2 aTexCoord;\n"
    "varying vec2 TexCoord;\n"
    "uniform mat4 uMVP;\n"
    "void main() {\n"
    "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
    "}\n";

const char* voxelFragmentShaderSrc = 
    "varying vec2TexCoord;\n"
    "uniform sampler2D uTexture;\n"
    "void main() {\n"
    "   gl_FragColor = texture2D(uTexture, TexCoord);\n"
    "}\n";

int main(int argc, char* argv[]) {
    std::cout << "=== STARTING VOXEL ENGINE (SURVIVAL & CREATIVE MODES) ===" << std::endl;

    Platform platform("Voxel Engine - Luanti Style", 1280, 720);
    Input input;
    Player player(glm::vec3(8.0f, 15.0f, 25.0f));
    Camera camera(player.position);

    World world;
    world.loadChunksAroundPlayer(0, 0, 1); // Завантажуємо стартові чанки

    Shader shader(voxelVertexShaderSrc, voxelFragmentShaderSrc);
    GLuint grassTexture = TextureLoader::loadTexturePNG("assets/textures/blocks/grass_top.png");

    bool isRunning = true;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    float deltaTime = 0.016f;

    while (isRunning) {
        input.handleEvents(isRunning);

        // Керування рухом гравця (WASD)
        if (input.isKeyPressed(SDL_SCANCODE_W)) camera.processKeyboard('W', deltaTime);
        if (input.isKeyPressed(SDL_SCANCODE_S)) camera.processKeyboard('S', deltaTime);
        if (input.isKeyPressed(SDL_SCANCODE_A)) camera.processKeyboard('A', deltaTime);
        if (input.isKeyPressed(SDL_SCANCODE_D)) camera.processKeyboard('D', deltaTime);

        // Перемикання режимів гри по клавіші 'F' (Виживання / Креатив)
        if (input.isKeyPressed(SDL_SCANCODE_F)) {
            player.toggleGameMode();
            std::cout << "Game Mode changed to: " << (player.gameMode == GameMode::Creative ? "Creative" : "Survival") << std::endl;
        }

        player.update(deltaTime);
        camera.position = player.position + glm::vec3(0.0f, player.eyeHeight, 0.0f);

        // Взаємодія зі світом мишею (ЛКМ - руйнування, ПКМ - встановлення блоку)
        if (input.isLeftMouseButtonPressed()) {
            RaycastResult res = Raycaster::raycast(camera.position, camera.front, world, 6.0f);
            if (res.hit) {
                world.setBlockAt(res.x, res.y, res.z, BlockType::Air); // Зносимо блок
            }
        }
        if (input.isRightMouseButtonPressed()) {
            RaycastResult res = Raycaster::raycast(camera.position, camera.front, world, 6.0f);
            if (res.hit) {
                world.setBlockAt(res.adjacentX, res.adjacentY, res.adjacentZ, BlockType::Stone); // Ставимо камінь
            }
        }

        // Рендеринг екрана
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(75.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 mvp = projection * view;

        shader.use();
        shader.setMat4("uMVP", &mvp[0][0]);

        Renderer::renderWorld(world, shader, grassTexture);

        platform.swapBuffers();
    }

    std::cout << "Engine shut down cleanly." << std::endl;
    return 0;
}
