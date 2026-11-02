#include <iostream>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "WorldGen.hpp"
#include "Crafting.hpp"
#include "Mob.hpp"

const int CHUNK_SIZE = 16;

// Структура чанка
struct Chunk {
    int x, z;
    std::vector<uint8_t> blocks;

    Chunk(int cx, int cz) : x(cx), z(cz) {
        blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, static_cast<uint8_t>(BlockType::Air));
        generate();
    }

    void generate() {
        for (int lx = 0; lx < CHUNK_SIZE; ++lx) {
            for (int lz = 0; lz < CHUNK_SIZE; ++lz) {
                int worldX = x * CHUNK_SIZE + lx;
                int worldZ = z * CHUNK_SIZE + lz;

                BiomeType biome = WorldGenerator::getBiome(worldX, worldZ);
                int height = WorldGenerator::getTerrainHeight(worldX, worldZ, biome);

                for (int ly = 0; ly < CHUNK_SIZE; ++ly) {
                    int idx = lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE;
                    if (ly < height - 3) {
                        blocks[idx] = static_cast<uint8_t>(BlockType::Stone);
                    } else if (ly < height) {
                        blocks[idx] = static_cast<uint8_t>(biome == BiomeType::Desert ? BlockType::Sand : BlockType::Dirt);
                    } else if (ly == height) {
                        blocks[idx] = static_cast<uint8_t>(biome == BiomeType::Desert ? BlockType::Sand : BlockType::Grass);
                    }
                }

                // Спавн дерева у лісовому біомі з певною ймовірністю
                if (biome == BiomeType::Forest && height < CHUNK_SIZE - 6 && (lx % 5 == 0 && lz % 5 == 0)) {
                    WorldGenerator::generateTree(blocks, lx, height + 1, lz, CHUNK_SIZE);
                }
            }
        }
    }
};

int main() {
    std::cout << "=== INITIALIZING NATIVE VOXEL ENGINE (C++) ===" << std::endl;

    // Створюємо базові системи
    CraftingSystem crafting;
    std::vector<std::unique_ptr<Mob>> mobs;

    // Спавним моба (наприклад, зомбі або кабан) у світі
    mobs.push_back(std::make_unique<Mob>("Zombie", 5.0f, 10.0f, 5.0f, true));

    // Генеруємо стартовий чанк (0, 0)
    Chunk spawnChunk(0, 0);
    std::cout << "Spawn chunk generated successfully at (0, 0)!" << std::endl;

    // Перевірка системи крафту
    BlockType outItem;
    int outCount;
    if (crafting.tryCraft(BlockType::Wood, 1, outItem, outCount)) {
        std::cout << "Crafting test passed! Crafted item ID: " << static_cast<int>(outItem) << " (Count: " << outCount << ")" << std::endl;
    }

    // Симуляція ігрового циклу (Game Loop)
    bool isRunning = true;
    float simulatedDeltaTime = 0.016f; // ~60 FPS

    std::cout << "Starting main game loop simulation..." << std::endl;
    for (int frame = 0; frame < 3; ++frame) {
        // Оновлення мовів
        for (auto& mob : mobs) {
            mob->update(simulatedDeltaTime, 0.0f, 0.0f);
            std::cout << "Mob [" << mob->name << "] position -> X: " << mob->x << ", Z: " << mob->z << std::endl;
        }
        std::cout << "--- Frame " << frame + 1 << " rendered ---" << std::endl;
    }

    std::cout << "Engine core running properly. Ready for OpenGL / Window integration!" << std::endl;
    return 0;
}
