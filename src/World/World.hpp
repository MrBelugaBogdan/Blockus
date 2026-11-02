#pragma once
#include "Chunk.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

class World {
private:
    // Зберігаємо чанки у хеш-таблиці за ключем "X,Z"
    std::unordered_map<std::string, std::unique_ptr<Chunk>> chunks;

    std::string getChunkKey(int x, int z) const {
        return std::to_string(x) + "," + std::to_string(z);
    }

public:
    // Завантаження чанків навколо певної позиції гравця (рендеринг-дистанція)
    void loadChunksAroundPlayer(int playerChunkX, int playerChunkZ, int renderDistance) {
        for (int x = -renderDistance; x <= renderDistance; ++x) {
            for (int z = -renderDistance; z <= renderDistance; ++z) {
                int cx = playerChunkX + x;
                int cz = playerChunkZ + z;
                std::string key = getChunkKey(cx, cz);

                if (chunks.find(key) == chunks.end()) {
                    // Якщо чанка ще немає в пам'яті — створюємо його
                    chunks[key] = std::make_unique<Chunk>(cx, cz);
                }
            }
        }
    }

    // Отримання посилання на всі активні чанки (для рендерера)
    const std::unordered_map<std::string, std::unique_ptr<Chunk>>& getChunks() const {
        return chunks;
    }

    // Пошук типу блоку за реальними глобальними світовими координатами (X, Y, Z)
    BlockType getBlockAt(int x, int y, int z) const {
        int cx = x >= 0 ? x / CHUNK_SIZE : (x - CHUNK_SIZE + 1) / CHUNK_SIZE;
        int cz = z >= 0 ? z / CHUNK_SIZE : (z - CHUNK_SIZE + 1) / CHUNK_SIZE;
        std::string key = getChunkKey(cx, cz);

        auto it = chunks.find(key);
        if (it == chunks.end()) return BlockType::Air;

        int lx = x - cx * CHUNK_SIZE;
        int lz = z - cz * CHUNK_SIZE;
        int ly = y;

        if (ly < 0 || ly >= CHUNK_SIZE) return BlockType::Air;
        return it->second->blocks[lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE];
    }

    // Зміна блоку за світовими координатами (руйнування або встановлення) із перерахунком мешу
    void setBlockAt(int x, int y, int z, BlockType type) {
        int cx = x >= 0 ? x / CHUNK_SIZE : (x - CHUNK_SIZE + 1) / CHUNK_SIZE;
        int cz = z >= 0 ? z / CHUNK_SIZE : (z - CHUNK_SIZE + 1) / CHUNK_SIZE;
        std::string key = getChunkKey(cx, cz);

        auto it = chunks.find(key);
        if (it != chunks.end()) {
            int lx = x - cx * CHUNK_SIZE;
            int lz = z - cz * CHUNK_SIZE;
            int ly = y;

            if (ly >= 0 && ly < CHUNK_SIZE) {
                it->second->blocks[lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE] = type;
                it->second->buildMesh(); // Миттєво оновлюємо видиму сітку чанка!
            }
        }
    }
};
