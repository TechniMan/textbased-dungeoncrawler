#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include <string>
#include <vector>

#include "Creature.hpp"

enum ITEMS {
    ITEM_NULL,
    ITEM_HEALTH_POTION
};

class Item {
private:
    Item(void) {}
    Item(const Item &) {}

public:
    static bool UseItem(ITEMS item, Creature& user, Creature& target) noexcept;
    static ITEMS GetByName(std::string name) noexcept;
    static std::string GetName(ITEMS item) noexcept;
};

#endif // _ITEMS_HPP_
