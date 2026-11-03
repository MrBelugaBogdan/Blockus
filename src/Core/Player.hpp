#pragma once
#include <glm/glm.hpp>

enum class GameMode {
    Survival = 0,
    Creative = 1
};

class Player {
public:
    glm::vec3 position;
    glm::vec3 velocity;
    GameMode gameMode;
    bool isGrounded;
    float eyeHeight;
    float speed;

    Player(glm::vec3 startPos) {
        position = startPos;
        velocity = glm::vec3(0.0f);
        gameMode = GameMode::Creative; // За замовчуванням у креативі для зручності тестів
        isGrounded = false;
        eyeHeight = 1.62f;
        speed = 5.0f;
    }

    // Перемикання режиму гри (наприклад, по натисканню клавіші)
    void toggleGameMode() {
        if (gameMode == GameMode::GameMode::Survival) {
            gameMode = GameMode::Creative;
            velocity = glm::vec3(0.0f);
        } else {
            gameMode = GameMode::GameMode::Survival;
        }
    }

    void update(float deltaTime) {
        if (gameMode == GameMode::Survival) {
            // У виживанні діє гравітація
            velocity.y -= 25.0f * deltaTime; // Прискорення вільного падіння
            position.y += velocity.y * deltaTime;

            // Тимчасова перевірка землі (надалі зв'яжемо з колізіями світу)
            if (position.y < 10.0f) {
                position.y = 10.0f;
                velocity.y = 0.0f;
                isGrounded = true;
            } else {
                isGrounded = false;
            }
        } else {
            // У креативі немає гравітації, гравець просто летить у просторі
            velocity = glm::vec3(0.0f);
        }
    }
};
