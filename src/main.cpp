#include <iostream>
#include <memory>
#include "Core/Platform.hpp"
#include "Core/Input.hpp"
#include "World/Chunk.hpp"

int main(int argc, char* argv[]) {
    std::cout << "=== STARTING MULTIPLATFORM VOXEL ENGINE ===" << std::endl;

    // Створюємо вікно (на ПК — вікно 1024x768, на телефоні — розгортається на весь екран)
    Platform platform("Voxel Engine - CrossPlatform", 1024, 768);
    Input input;

    // Генеруємо перший тестовий чанк світу
    Chunk spawnChunk(0, 0);
    std::cout << "Spawn chunk generated with blocks!" << std::endl;

    bool isRunning = true;

    // Головний ігровий цикл
    while (isRunning) {
        input.handleEvents(isRunning);

        // Очищення екрана у класичний колір неба Luanti
        // (Команди сумісні зі старим OpenGL 2.1 та ES 2.0)
        // glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        platform.swapBuffers();
    }

    std::cout << "Engine shut down cleanly." << std::endl;
    return 0;
}
