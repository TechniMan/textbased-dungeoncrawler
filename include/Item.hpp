#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include <string>
#include <vector>

#include "Creature.hpp"

enum Items {
    ITEM_NULL,
    ITEM_HEALTH_POTION
};

struct Item {
    uint id;
    std::string name;

    Item(uint itemId, std::string itemName);
    Item(const Item&);
    std::string ToString(void) const noexcept;

    static bool UseItem(Items item, Creature& user, Creature& target) noexcept;
    static Item GetByName(std::string name) noexcept;
};

#endif // _ITEMS_HPP_
