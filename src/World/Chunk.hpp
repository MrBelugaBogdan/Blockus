#pragma once
#include "Block.hpp"
#include <vector>

const int CHUNK_SIZE = 16;

class Chunk {
public:
    int x, z;
    std::vector<BlockType> blocks;
    std::vector<float> vertices; // Вершини для OpenGL рендерингу

    Chunk(int chunkX, int chunkZ) : x(chunkX), z(chunkZ) {
        blocks.resize(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, BlockType::Air);
        generateTerrain();
        buildMesh();
    }

    void generateTerrain() {
        for (int lx = 0; lx < CHUNK_SIZE; ++lx) {
            for (int lz = 0; lz < CHUNK_SIZE; ++lz) {
                for (int ly = 0; ly < 4; ++ly) { // Невеликий шар землі для старта
                    int index = lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE;
                    blocks[index] = BlockType::Grass;
                }
            }
        }
    }

    // Проста генерація кубиків для рендерингу
    void buildMesh() {
        vertices.clear();
        // Для кожного блоку повітря/землі створюємо базові дані
        for (int lx = 0; lx < CHUNK_SIZE; ++lx) {
            for (int ly = 0; ly < CHUNK_SIZE; ++ly) {
                for (int lz = 0; lz < CHUNK_SIZE; ++lz) {
                    int index = lx + ly * CHUNK_SIZE + lz * CHUNK_SIZE * CHUNK_SIZE;
                    if (blocks[index] != BlockType::Air) {
                        // Додаємо координати простого куба (X, Y, Z, Колір/Текстура)
                        float fx = (float)lx + (x * CHUNK_SIZE);
                        float fy = (float)ly;
                        float fz = (float)lz + (z * CHUNK_SIZE);

                        // Тимчасовий простий куб (шість вершин для прикладу)
                        float cubeVertices[] = {
                            fx, fy, fz,       // позиція
                            fx + 1, fy, fz,
                            fx + 1, fy + 1, fz,
                            
                            fx + 1, fy + 1, fz,
                            fx, fy + 1, fz,
                            fx, fy, fz
                        };
                        
                        // Додаємо в загальний буфер
                        for (float v : cubeVertices) {
                            vertices.push_back(v);
                        }
                    }
                }
            }
        }
    }
};
