#pragma once
#include <glm/glm.hpp>
#include <cmath>
#include "World.hpp"
#include "Block.hpp"

struct RaycastResult {
    bool hit = false;
    int x, y, z;
    int adjacentX, adjacentY, adjacentZ;
    BlockType blockType;
};

class Raycaster {
public:
    static RaycastResult raycast(const glm::vec3& cameraPos, const glm::vec3& cameraDir, const World& world, float maxDistance) {
        RaycastResult result;
        float stepSize = 0.05f;

        for (float t = 0.0f; t < maxDistance; t += stepSize) {
            glm::vec3 pos = cameraPos + cameraDir * t;
            int bx = static_cast<int>(std::floor(pos.x));
            int by = static_cast<int>(std::floor(pos.y));
            int bz = static_cast<int>(std::floor(pos.z));

            BlockType type = world.getBlockAt(bx, by, bz);
            if (type != BlockType::Air) {
                result.hit = true;
                result.x = bx;
                result.y = by;
                result.z = bz;
                result.blockType = type;

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
