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

    const std::unordered_map<std::string, std::unique_ptr<Chunk>>& getChunks() const {
        return chunks;
    }
};
