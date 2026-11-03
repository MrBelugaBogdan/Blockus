#pragma once
#include <vector>
#include "../World/Block.hpp"
#include "Inventory.hpp"

struct CraftingRecipe {
    BlockType inputItem;
    int inputCount;
    BlockType outputItem;
    int outputCount;
};

class CraftingSystem {
private:
    std::vector<CraftingRecipe> recipes;

public:
    CraftingSystem() {
        // Додаємо базові рецепти Luanti-стилю
        recipes.push_back({BlockType::Wood, 1, BlockType::Dirt, 4});   // З 1 блоку дерева виходить 4 блоки землі/матеріалу
        recipes.push_back({BlockType::Stone, 2, BlockType::Wood, 1});  // Приклад обміну ресурсів
    }

    bool craft(Inventory& inv, int recipeIndex) {
        if (recipeIndex < 0 || recipeIndex >= recipes.size()) return false;
        const auto& recipe = recipes[recipeIndex];

        // Перевіряємо, чи є потрібний ресурс в інвентарі
        // (Для спрощення шукаємо будь-який слот із відповідним інгредієнтом)
        for (int i = 0; i < 9; ++i) {
            ItemStack slot = inv.getSlot(i);
            if (slot.type == recipe.inputItem && slot.count >= recipe.inputCount) {
                // Вилучаємо інгредієнти і додаємо результат
                inv.removeItem(i, recipe.inputCount);
                inv.addItem(recipe.outputItem, recipe.outputCount);
                return true;
            }
        }
        return false;
    }

    const std::vector<CraftingRecipe>& getRecipes() const {
        return recipes;
    }
};
