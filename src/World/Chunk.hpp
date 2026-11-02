#pragma once
#include "Block.hpp"
#include <vector>

const int CHUNK_SIZE = 16;

struct Vertex {
    float x, y, z;    // Позиція вершини в 3D
    float u, v;       // Текстурні координати (UV для PNG)
};

class Chunk {
public:
    int x, z;
    std::vector<BlockType> blocks;
    std::vector<Vertex> vertices;

    Chunk(int chunkX, int chunkZ) : x(chunkX), z(chunkZ) {
        blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, BlockType::Air);
        generateTerrain();
        buildMesh();
    }

    void generateTerrain() {
        for (int lx = 0; lx < CHUNK_SIZE; ++lx) {
            for (int lz = 0; lz < CHUNK_SIZE; ++lz) {
                // Висота рельєфу для простого стартового холма
                int height = 4 + (lx % 3); 
                for (int ly = 0; ly <= height; ++ly) {
                    int index = lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE;
                    if (ly == height) blocks[index] = BlockType::Grass;
                    else if (ly > height - 2) blocks[index] = BlockType::Dirt;
                    else blocks[index] = BlockType::Stone;
                }
            }
        }
    }

    BlockType getBlock(int lx, int ly, int lz) const {
        if (lx < 0 || lx >= CHUNK_SIZE || ly < 0 || ly >= CHUNK_SIZE || lz < 0 || lz >= CHUNK_SIZE)
            return BlockType::Air; // За межами чанка — повітря
        return blocks[lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE];
    }

    // Головна оптимізація: Face Culling (малюємо тільки видимі грані)
    void buildMesh() {
        vertices.clear();

        for (int lx = 0; lx < CHUNK_SIZE; ++lx) {
            for (int ly = 0; ly < CHUNK_SIZE; ++ly) {
                for (int lz = 0; lz < CHUNK_SIZE; ++lz) {
                    BlockType current = getBlock(lx, ly, lz);
                    if (current == BlockType::Air) continue;

                    float wx = (float)(lx + x * CHUNK_SIZE);
                    float wy = (float)ly;
                    float wz = (float)(lz + z * CHUNK_SIZE);

                    // Перевірка 6 граней куба (Зверху, Знизу, Зліва, Справа, Зпереду, Ззаду)
                    
                    // Верхня грань (+Y)
                    if (getBlock(lx, ly + 1, lz) == BlockType::Air) {
                        addFace(wx, wy + 1, wz,  wx + 1, wy + 1, wz,  wx + 1, wy + 1, wz + 1,  wx, wy + 1, wz + 1);
                    }
                    // Нижня грань (-Y)
                    if (getBlock(lx, ly - 1, lz) == BlockType::Air) {
                        addFace(wx, wy, wz + 1,  wx + 1, wy, wz + 1,  wx + 1, wy, wz,  wx, wy, wz);
                    }
                    // Передня грань (+Z)
                    if (getBlock(lx, ly, lz + 1) == BlockType::Air) {
                        addFace(wx, wy, wz + 1,  wx + 1, wy, wz + 1,  wx + 1, wy + 1, wz + 1,  wx, wy + 1, wz + 1);
                    }
                    // Задня грань (-Z)
                    if (getBlock(lx, ly, lz - 1) == BlockType::Air) {
                        addFace(wx + 1, wy, wz,  wx, wy, wz,  wx, wy + 1, wz,  wx + 1, wy + 1, wz);
                    }
                    // Права грань (+X)
                    if (getBlock(lx + 1, ly, lz) == BlockType::Air) {
                        addFace(wx + 1, wy, wz + 1,  wx + 1, wy, wz,  wx + 1, wy + 1, wz,  wx + 1, wy + 1, wz + 1);
                    }
                    // Ліва грань (-X)
                    if (getBlock(lx - 1, ly, lz) == BlockType::Air) {
                        addFace(wx, wy, wz,  wx, wy, wz + 1,  wx, wy + 1, wz + 1,  wx, wy + 1, wz);
                    }
                }
            }
        }
    }

private:
    void addFace(float x1, float y1, float z1, float x2, float y2, float z2, 
                 float x3, float y3, float z3, float x4, float y4, float z4) {
        // Додаємо два трикутники для прямокутної грані з UV координатами
        vertices.push_back({x1, y1, z1, 0.0f, 0.0f});
        vertices.push_back({x2, y2, z2, 1.0f, 0.0f});
        vertices.push_back({x3, y3, z3, 1.0f, 1.0f});

        vertices.push_back({x1, y1, z1, 0.0f, 0.0f});
        vertices.push_back({x3, y3, z3, 1.0f, 1.0f});
        vertices.push_back({x4, y4, z4, 0.0f, 1.0f});
    }
};
