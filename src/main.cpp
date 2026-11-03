#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Platform.hpp"
#include "Core/Input.hpp"
#include "Core/Camera.hpp"
#include "Core/Player.hpp"
#include "Core/SaveSystem.hpp"
#include "World/World.hpp"
#include "World/Raycast.hpp"
#include "Render/Shader.hpp"
#include "Render/Renderer.hpp"
#include "Render/TextureLoader.hpp"
#include "UI/Menu.hpp"
#include "UI/TouchControls.hpp"
#include "Audio/SoundManager.hpp"

// Шейдери для OpenGL 2.1 / ES 2.0 (працюють і на ПК, і на мобільних)
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
    "varying vec2 TexCoord;\n"
    "uniform sampler2D uTexture;\n"
    "void main() {\n"
    "   gl_FragColor = texture2D(uTexture, TexCoord);\n"
    "}\n";

int main(int argc, char* argv[]) {
    std::cout << "=== INITIALIZING NATIVE VOXEL ENGINE (LUANTI STYLE) ===" << std::endl;

    // Створюємо вікно 1280x720
    Platform platform("Voxel Engine - Full Game", 1280, 720);
    Input input;
    GameMenu menu;
    SoundManager soundManager;

    // Завантажуємо тестові звуки (якщо вони є в папці assets/sounds/)
    soundManager.loadSound("break", "assets/sounds/block_break.wav");
    soundManager.loadSound("place", "assets/sounds/block_place.wav");

    Player player(glm::vec3(8.0f, 15.0f, 25.0f));
    Camera camera(player.position);

    World world;
    // Завантажуємо збережений світ або генерируємо новий за замовчуванням
    SaveSystem::loadWorld("autosave.dat", world);
    if (world.getChunks().empty()) {
        world.loadChunksAroundPlayer(0, 0, 1);
    }

    Shader shader(voxelVertexShaderSrc, voxelFragmentShaderSrc);
    GLuint grassTexture = TextureLoader::loadTexturePNG("assets/textures/blocks/grass_top.png");

    bool isRunning = true;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    float deltaTime = 0.016f;

    while (isRunning) {
        input.handleEvents(isRunning);

        // Якщо ми в Головному меню або Налаштуваннях
        if (menu.getState() == GameState::MainMenu || menu.getState() == GameState::Settings) {
            // Очищення екрана для меню
            glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Якщо клікнули мишею — перевіряємо кнопки меню
            if (input.isLeftMouseButtonPressed()) {
                // Умовно передаємо координати кліку (наприклад, центр екрана)
                menu.handleMenuClick(640, 360, 1280, 720);
            }

            if (menu.getState() == GameState::Exited) {
                isRunning = false;
            }

            platform.swapBuffers();
            continue; // Пропускаємо ігровий цикл, поки гравець у меню
        }

        // --- ІГРОВИЙ ПРОЦЕС (Коли натиснуто "Грати") ---

        // Керування рухом гравця (WASD)
        if (input.isKeyPressed(SDL_SCANCODE_W)) camera.processKeyboard('W', deltaTime);
        if (input.isKeyPressed(SDL_SCANCODE_S)) camera.processKeyboard('S', deltaTime);
        if (input.isKeyPressed(SDL_SCANCODE_A)) camera.processKeyboard('A', deltaTime);
        if (input.isKeyPressed(SDL_SCANCODE_D)) camera.processKeyboard('D', deltaTime);

        // Перемикання режимів гри по клавіші 'F' (Виживання / Креатив)
        if (input.isKeyPressed(SDL_SCANCODE_F)) {
            player.toggleGameMode();
            std::cout << "Game Mode: " << (player.gameMode == GameMode::Creative ? "Creative" : "Survival") << std::endl;
        }

        player.update(deltaTime);
        camera.position = player.position + glm::vec3(0.0f, player.eyeHeight, 0.0f);

        // Взаємодія зі світом мишею (ЛКМ - руйнування, ПКМ - встановлення блоку)
        if (input.isLeftMouseButtonPressed()) {
            RaycastResult res = Raycaster::raycast(camera.position, camera.front, world, 6.0f);
            if (res.hit) {
                world.setBlockAt(res.x, res.y, res.z, BlockType::Air);
                soundManager.playSound("break");
            }
        }
        if (input.isRightMouseButtonPressed()) {
            RaycastResult res = Raycaster::raycast(camera.position, camera.front, world, 6.0f);
            if (res.hit) {
                world.setBlockAt(res.adjacentX, res.adjacentY, res.adjacentZ, BlockType::Stone);
                soundManager.playSound("place");
            }
        }

        // Рендеринг 3D світу
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

    // Автоматичне збереження світу при виході з гри
    SaveSystem::saveWorld("autosave.dat", world);
    std::cout << "Engine shut down cleanly. World saved." << std::endl;
    return 0;
}
