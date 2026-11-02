#pragma once
#include <string>
#include <cmath>

class Mob {
public:
    std::string name;
    float x, y, z;
    float health;
    float speed;
    bool isHostile; // Ворожий (для майбутнього PvP/PvE)

    Mob(std::string mobName, float startX, float startY, float startZ, bool hostile)
        : name(mobName), x(startX), y(startY), z(startZ), health(20.0f), speed(3.0f), isHostile(hostile) {}

    void update(float deltaTime, float targetX, float targetZ) {
        // Простий штучний інтелект: рух у бік гравця, якщо він поруч
        float dx = targetX - x;
        float dz = targetZ - z;
        float dist = std::sqrt(dx * dx + dz * dz);

        if (dist > 1.0f && dist < 15.0f) {
            x += (dx / dist) * speed * deltaTime;
            z += (dz / dist) * speed * deltaTime;
        }
    }
};
