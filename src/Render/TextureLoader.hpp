#pragma once
#include <iostream>
#include <string>

// Визначаємо макрос для завантаження зображень
#define STB_IMAGE_IMPLEMENTATION
// Заглушка, щоб ти міг підключити реальний файл stb_image.h з інтернету в папку src/Render/
// (або ми інтегруємо його в наступних кроках)

#if defined(__ANDROID__) || defined(__IPHONEOS__)
#include <GLES2/gl2.h>
#else
#include <SDL_opengl.h>
#endif

class TextureLoader {
public:
    static GLuint loadTexturePNG(const std::string& filepath) {
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Налаштування для піксель-арту (чіткі кубики без розмиття)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Тимчасова заглушка завантаження (поки немає файлу stb_image.h)
        std::cout << "Loading texture from: " << filepath << " (Pending stb_image setup)" << std::endl;

        return textureID;
    }
};
