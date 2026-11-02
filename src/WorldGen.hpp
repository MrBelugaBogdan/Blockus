#pragma once
#include "Block.hpp"
#include <vector>
#include <cmath>
#include <cstdlib>

enum class BiomeType {
    Forest,
    Desert,
    Mountains
};

class WorldGenerator {
public:
    static BiomeType getBiome(int x, int z) {
        // Простий математичний шум для вибору біому
        float noise = std::sin(x * 0.03f) * std::cos(z * 0.03f);
        if (noise > 0.35f) return BiomeType::Desert;
        if (noise < -0.35f) return BiomeType::Mountains;
        return BiomeType::Forest;
    }

    static int getTerrainHeight(int x, int z, BiomeType biome) {
        float base = std::sin(x * 0.1f) * std::cos(z * 0.1f);
        if (biome == BiomeType::Mountains) {
            return static_cast<int>(base * 10.0f + 20.0f); // Високі гори
        } else if (biome == BiomeType::Desert) {
            return static_cast<int>(base * 2.0f + 6.0f);   // Рівні дюни
        }
        return static_cast<int>(base * 4.0f + 10.0f);      // Ліс
    }

    // Генерація дерева у чанку
    static void generateTree(std::vector<uint8_t>& blocks, int localX, int baseHeight, int localZ, int chunkSize) {
        // Стовбур дерева (висота 4 блока)
        for (int y = baseHeight; y < baseHeight + 4; ++y) {
            if (y < chunkSize) {
                int idx = localX + y * chunkSize + localZ * chunkSize * chunkSize;
                blocks[idx] = static_cast<uint8_t>(BlockType::Wood);
            }
        }

        // Крона листя
        for (int ly = baseHeight + 3; ly <= baseHeight + 5; ++ly) {
            for (int lx = localX - 1; lx <= localX + 1; ++lx) {
                for (int lz = localZ - 1; lz <= localZ + 1; ++lz) {
                    if (lx >= 0 && lx < chunkSize && lz >= 0 && lz < chunkSize && ly < chunkSize) {
                        int idx = lx + ly * chunkSize + lz * chunkSize * chunkSize;
                        if (blocks[idx] == static_cast<uint8_t>(BlockType::Air)) {
                            blocks[idx] = static_cast<uint8_t>(BlockType::Leaves);
                        }
                    }
                }
            }
        }
    }
};
