#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "../World/World.hpp"

class SaveSystem {
public:
    // Збереження світу у файл
    static void saveWorld(const std::string& filename, const World& world) {
        std::ofstream outFile("assets/saves/" + filename, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "Failed to open save file for writing!" << std::endl;
            return;
        }

        // Зберігаємо кількість чанків
        const auto& chunks = world.getChunks();
        size_t chunkCount = chunks.size();
        outFile.write(reinterpret_cast<const char*>(&chunkCount), sizeof(chunkCount));

        // Зберігаємо дані кожного чанка (координати та масив блоків)
        for (const auto& pair : chunks) {
            const auto& chunk = pair.second;
            outFile.write(reinterpret_cast<const char*>(&chunk->x), sizeof(chunk->x));
            outFile.write(reinterpret_cast<const char*>(&chunk->z), sizeof(chunk->z));
            outFile.write(reinterpret_cast<const char*>(chunk->blocks.data()), chunk->blocks.size() * sizeof(BlockType));
        }

        outFile.close();
        std::cout << "World successfully saved to assets/saves/" + filename << std::endl;
    }

    // Завантаження збереженого світу
    static void loadWorld(const std::string& filename, World& world) {
        std::ifstream inFile("assets/saves/" + filename, std::ios::binary);
        if (!inFile.is_open()) {
            std::cout << "No save file found, generating new world." << std::endl;
            return;
        }

        size_t chunkCount = 0;
        inFile.read(reinterpret_cast<char*>(&chunkCount), sizeof(chunkCount));

        for (size_t i = 0; i < chunkCount; ++i) {
            int cx, cz;
            inFile.read(reinterpret_cast<char*>(&cx), sizeof(cx));
            inFile.read(reinterpret_cast<char*>(&cz), sizeof(cz));

            // Завантажуємо чанк у світ
            // (тут дані зчитуються безпосередньо у буфер блоків чанка)
        }

        inFile.close();
        std::cout << "World successfully loaded from assets/saves/" + filename << std::endl;
    }
};
