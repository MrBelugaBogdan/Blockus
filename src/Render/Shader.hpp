#pragma once
#include <string>
#include <iostream>

#if defined(__ANDROID__) || defined(__IPHONEOS__)
#include <GLES2/gl2.h>
#else
#include <SDL_opengl.h>
#endif

class Shader {
public:
    GLuint id;

    Shader(const char* vertexSrc, const char* fragmentSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
        glCompileShader(fragmentShader);

        id = glCreateProgram();
        glAttachShader(id, vertexShader);
        glAttachShader(id, fragmentShader);
        glLinkProgram(id);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use() {
        glUseProgram(id);
    }

    void setMat4(const std::string& name, const float* mat) const {
        GLint loc = glGetUniformLocation(id, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
    }

    void setInt(const std::string& name, int value) const {
        GLint loc = glGetUniformLocation(id, name.c_str());
        glUniform1i(loc, value);
    }
};
