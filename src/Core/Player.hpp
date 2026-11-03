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
        gameMode = GameMode::Creative; // Починаємо в креативі для зручності
        isGrounded = false;
        eyeHeight = 1.62f;
        speed = 6.0f;
    }

    void toggleGameMode() {
        if (gameMode == GameMode::GameMode::Survival) {
            gameMode = GameMode::Creative;
            velocity = glm::vec3(0.0f);
        } else {
            gameMode = GameMode::Survival;
        }
    }

    void update(float deltaTime) {
        if (gameMode == GameMode::Survival) {
            // У виживанні працює гравітація
            velocity.y -= 25.0f * deltaTime;
            position.y += velocity.y * deltaTime;

            // Тимчасова підлога на висоті 10
            if (position.y < 10.0f) {
                position.y = 10.0f;
                velocity.y = 0.0f;
                isGrounded = true;
            } else {
                isGrounded = false;
            }
        } else {
            // У креативі зупиняємо вертикальну швидкість для польоту
            velocity.y = 0.0f;
        }
    }
};
