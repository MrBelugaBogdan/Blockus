#pragma once
#include <string>
#include <iostream>

enum class GameState {
    MainMenu = 0,
    Settings = 1,
    Playing = 2,
    Exited = 3
};

class GameMenu {
private:
    GameState currentState;

public:
    GameMenu() : currentState(GameState::MainMenu) {}

    GameState getState() const { return currentState; }

    // Обробка натискань у меню (управління мишею або дотиком)
    void handleMenuClick(int mouseX, int mouseY, int screenWidth, int screenHeight) {
        if (currentState == GameState::MainMenu) {
            // Кнопка "Грати" (умовно по центру екрана)
            if (mouseX >= screenWidth / 2 - 150 && mouseX <= screenWidth / 2 + 150 &&
                mouseY >= screenHeight / 2 - 50 && mouseY <= screenHeight / 2) {
                currentState = GameState::Playing;
                std::cout << "Starting Game..." << std::endl;
            }
            // Кнопка "Налаштування"
            else if (mouseX >= screenWidth / 2 - 150 && mouseX <= screenWidth / 2 + 150 &&
                      mouseY >= screenHeight / 2 + 20 && mouseY <= screenHeight / 2 + 70) {
                currentState = GameState::Settings;
                std::cout << "Opening Settings..." << std::endl;
            }
            // Кнопка "Вихід"
            else if (mouseX >= screenWidth / 2 - 150 && mouseX <= screenWidth / 2 + 150 &&
                      mouseY >= screenHeight / 2 + 90 && mouseY <= screenHeight / 2 + 140) {
                currentState = GameState::Exited;
                std::cout << "Exiting Game..." << std::endl;
            }
        } 
        else if (currentState == GameState::Settings) {
            // Кнопка "Назад" у налаштуваннях
            if (mouseX >= 50 && mouseX <= 200 && mouseY >= 50 && mouseY <= 100) {
                currentState = GameState::MainMenu;
                std::cout << "Returning to Main Menu..." << std::endl;
            }
        }
    }

    // Рендеринг меню (тут твої PNG картинки накладаються на фон та кнопки)
    void render() {
        if (currentState == GameState::MainMenu) {
            // Рендер фону з assets/textures/ui/main_menu_bg.png
            // Рендер кнопок з assets/textures/ui/button_normal.png
        } else if (currentState == GameState::Settings) {
            // Рендер екрану налаштувань (гучність, дистанція промальовування, управління)
        }
    }
};
