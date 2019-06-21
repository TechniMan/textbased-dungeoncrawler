#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include <string>
#include <vector>

#include "Creature.hpp"

enum class ITEMS {
    NULL_ITEM,
    HEALTH_POTION
};

namespace Item {
    bool UseItem(ITEMS item, Creature& user, Creature& target) noexcept;
    ITEMS GetByName(std::string name) noexcept;
    std::string GetName(ITEMS item) noexcept;
};

#endif // _ITEMS_HPP_
