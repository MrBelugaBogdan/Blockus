#include <iostream>
#include "Platform.hpp"

int main(int argc, char* argv[]) {
    std::cout << "=== STARTING LUANTI-STYLE ENGINE (OLD LAPTOP COMPATIBLE) ===" << std::endl;

    // Створюємо вікно двигуна
    PlatformWindow window("Voxel Engine - Retro/OldPC Compatible", 1024, 768);

    // Головний ігровий цикл
    while (window.isRunning()) {
        window.pollEvents();

        // Очищуємо екран у звичний класичний колір неба Luanti
        // (Використовуємо класичні команди OpenGL 2.1, які працюють всюди)
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Увімкнемо, коли додамо буфер глибини

        window.swapBuffers();
    }

    std::cout << "Engine closed safely." << std::endl;
    return 0;
}
