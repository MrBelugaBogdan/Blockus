#pragma once
#include "Block.hpp"
#include <vector>

const int CHUNK_SIZE = 16;

class Chunk {
public:
    int x, z;
    std::vector<BlockType> blocks;

    Chunk(int chunkX, int chunkZ) : x(chunkX), z(chunkZ) {
        blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, BlockType::Air);
        generateTerrain();
    }

    void generateTerrain() {
        for (int lx = 0; lx < CHUNK_SIZE; ++lx) {
            for (int lz = 0; lz < CHUNK_SIZE; ++lz) {
                for (int ly = 0; ly < 8; ++ly) { // Простий базовий шар землі
                    int index = lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE;
                    if (ly < 6) blocks[index] = BlockType::Stone;
                    else if (ly < 7) blocks[index] = BlockType::Dirt;
                    else blocks[index] = BlockType::Grass;
                }
            }
        }
    }
};
