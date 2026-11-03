#pragma once
#include <vector>
#include <utility>
#include "../World/Block.hpp"

struct ItemStack {
    BlockType type;
    int count;

    ItemStack(BlockType t = BlockType::Air, int c = 0) : type(t), count(c) {}
};

class Inventory {
private:
    std::vector<ItemStack> slots;
    int capacity;

public:
    Inventory(int size = 9) : capacity(size) {
        slots.resize(capacity, ItemStack(BlockType::Air, 0));
    }

    bool addItem(BlockType type, int count) {
        // Спочатку шукаємо вже наявний такий самий блок у слотах
        for (auto& slot : slots) {
            if (slot.type == type) {
                slot.count += count;
                return true;
            }
        }
        // Якщо немає, шукаємо вільний слот
        for (auto& slot : slots) {
            if (slot.type == BlockType::Air || slot.count <= 0) {
                slot.type = type;
                slot.count = count;
                return true;
            }
        }
        return false; // Інвентар повний
    }

    bool removeItem(int slotIndex, int count) {
        if (slotIndex < 0 || slotIndex >= capacity) return false;
        if (slots[slotIndex].count >= count) {
            slots[slotIndex].count -= count;
            if (slots[slotIndex].count <= 0) {
                slots[slotIndex].type = BlockType::Air;
                slots[slotIndex].count = 0;
            }
            return true;
        }
        return false;
    }

    ItemStack getSlot(int index) const {
        if (index < 0 || index >= capacity) return ItemStack(BlockType::Air, 0);
        return slots[index];
    }
};
