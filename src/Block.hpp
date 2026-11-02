#pragma once
#include <cstdint>
#include <string>

enum class BlockType : uint8_t {
    Air = 0,
    Grass,
    Dirt,
    Stone,
    Wood,
    Leaves,
    Sand,
    Cactus,
    Water
};

struct BlockProperties {
    std::string name;
    bool isSolid;
    bool isTransparent;
    int hardness;
};

inline BlockProperties getBlockProps(BlockType type) {
    switch (type) {
        case BlockType::Air:     return {"Air", false, true, 0};
        case BlockType::Grass:   return {"Grass", true, false, 2};
        case BlockType::Dirt:    return {"Dirt", true, false, 1};
        case BlockType::Stone:   return {"Stone", true, false, 5};
        case BlockType::Wood:    return {"Wood", true, false, 3};
        case BlockType::Leaves:  return {"Leaves", true, true, 1};
        case BlockType::Sand:    return {"Sand", true, false, 1};
        case BlockType::Cactus:  return {"Cactus", true, false, 2};
        case BlockType::Water:   return {"Water", false, true, 0};
        default:                 return {"Unknown", false, true, 0};
    }
}
