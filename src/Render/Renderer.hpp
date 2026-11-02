#pragma once
#include <vector>
#include "../World/World.hpp"
#include "Shader.hpp"

#if defined(__ANDROID__) || defined(__IPHONEOS__)
#include <GLES2/gl2.h>
#else
#include <SDL_opengl.h>
#endif

class Renderer {
public:
    static void renderWorld(const World& world, Shader& shader, GLuint textureID) {
        shader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        shader.setInt("uTexture", 0);

        // Проходимо по всіх чанках світу
        for (const auto& pair : world.getChunks()) {
            const auto& chunk = pair.second;
            if (chunk->vertices.empty()) continue;

            GLuint vao, vbo;
            glGenBuffers(1, &vbo);
            
            // Передаємо вершини у відеокарту
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, chunk->vertices.size() * sizeof(Vertex), chunk->vertices.data(), GL_STATIC_DRAW);

            // Налаштування атрибутів позиції (x, y, z)
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

            // Налаштування атрибутів текстури (u, v)
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

            // Малювання граней чанка
            glDrawArrays(GL_TRIANGLES, 0, chunk->vertices.size());

            // Очищення пам'яті буфера
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDeleteBuffers(1, &vbo);
        }
    }
};
