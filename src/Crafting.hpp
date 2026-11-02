#pragma once
#include "Block.hpp"
#include <vector>

struct CraftingRecipe {
    BlockType input;
    int inputCount;
    BlockType output;
    int outputCount;
};

class CraftingSystem {
private:
    std::vector<CraftingRecipe> recipes;

public:
    CraftingSystem() {
        // Базові рецепти (як у Luanti/Minecraft)
        recipes.push_back({BlockType::Wood, 1, BlockType::Dirt, 4}); // Приклад: дерево розбивається на дошки/матеріал
        recipes.push_back({BlockType::Stone, 2, BlockType::Wood, 1}); // Приклад іншого крафту
    }

    bool tryCraft(BlockType inputItem, int inputCount, BlockType& outItem, int& outCount) {
        for (const auto& recipe : recipes) {
            if (recipe.input == inputItem && inputCount >= recipe.inputCount) {
                outItem = recipe.output;
                outCount = recipe.outputCount;
                return true;
            }
        }
        return false;
    }
};
