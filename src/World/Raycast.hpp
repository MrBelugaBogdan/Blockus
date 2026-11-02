#pragma once
#include <glm/glm.hpp>
#include "World.hpp"
#include "Block.hpp"

struct RaycastResult {
    bool hit = false;
    int x, y, z;          // Координати знайденого блоку
    int adjacentX, adjacentY, adjacentZ; // Координати сусіднього повітря (куди ставити новий блок)
    BlockType blockType;
};

class Raycaster {
public:
    static RaycastResult raycast(const glm::vec3& cameraPos, const glm::vec3& cameraDir, World& world, float maxDistance) {
        RaycastResult result;
        float stepSize = 0.05f; // Крок променя для точності

        for (float t = 0.0f; t < maxDistance; t += stepSize) {
            glm::vec3 pos = cameraPos + cameraDir * t;
            int bx = static_cast<int>(std::floor(pos.x));
            int by = static_cast<int>(std::floor(pos.y));
            int bz = static_cast<int>(std::floor(pos.z));

            // Перевіряємо блок у цій позиції
            BlockType type = world.getBlockAt(bx, by, bz);
            if (type != BlockType::Air) {
                result.hit = true;
                result.x = bx;
                result.y = by;
                result.z = bz;
                result.blockType = type;

                // Знаходимо попередню точку променя для встановлення блоку поруч
                glm::vec3 prevPos = cameraPos + cameraDir * (t - stepSize);
                result.adjacentX = static_cast<int>(std::floor(prevPos.x));
                result.adjacentY = static_cast<int>(std::floor(prevPos.y));
                result.adjacentZ = static_cast<int>(std::floor(prevPos.z));
                return result;
            }
        }
        return result;
    }
};
