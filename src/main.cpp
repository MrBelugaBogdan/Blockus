#include <iostream>
#include <vector>
#include "Core/Platform.hpp"
#include "Core/Input.hpp"
#include "World/Chunk.hpp"
#include "Render/Shader.hpp"

// Прості шейдери для OpenGL 2.1 (працюють навіть на калькуляторах і старих AMD)
const char* vertexShaderSrc = 
    "attribute vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos * 0.05, 1.0);\n" // Зменшуємо масштаб, щоб бачити світ
    "}\n";

const char* fragmentShaderSrc = 
    "void main() {\n"
    "   gl_FragColor = vec4(0.3, 0.7, 0.2, 1.0);\n" // Зелений колір трави
    "}\n";

int main(int argc, char* argv[]) {
    std::cout << "=== STARTING VOXEL ENGINE WITH RENDERER ===" << std::endl;

    Platform platform("Voxel Engine - 3D Render", 1024, 768);
    Input input;

    // Створюємо чанк світу
    Chunk spawnChunk(0, 0);
    std::cout << "Chunk mesh vertices count: " << spawnChunk.vertices.size() << std::endl;

    // Створюємо шейдерну програму
    Shader shader(vertexShaderSrc, fragmentShaderSrc);

    bool isRunning = true;

    // Увімкнемо буфер глибини, щоб кубики правильно накладалися один на один
    glEnable(GL_DEPTH_TEST);

    while (isRunning) {
        input.handleEvents(isRunning);

        // Очищення екрана (небо + глибина)
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Малюємо згенеровані блоки чанка
        if (!spawnChunk.vertices.empty()) {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), spawnChunk.vertices.data());
            
            glDrawArrays(GL_TRIANGLES, 0, spawnChunk.vertices.size() / 3);
            
            glDisableVertexAttribArray(0);
        }

        platform.swapBuffers();
    }

    std::cout << "Engine shut down cleanly." << std::endl;
    return 0;
}
