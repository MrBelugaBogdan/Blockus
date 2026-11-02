#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
private:
    GLFWwindow* window;
    int width, height;

public:
    Window(int w, int h, const char* title) : width(w), height(h) {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW!" << std::endl;
            exit(-1);
        }

        // Налаштування OpenGL контексту
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Вмикаємо VSync (обмеження кадрів)
    }

    ~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void swapBuffers() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    bool isKeyPressed(int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }
};
