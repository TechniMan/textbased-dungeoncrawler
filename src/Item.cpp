#include "Item.hpp"
#include "Utilities.hpp"

ITEMS Item::GetByName(std::string name) noexcept {
    ITEMS result = ITEMS::NULL_ITEM;

    if (to_lower(name) == "health potion") {
        result = ITEMS::HEALTH_POTION;
    }
    
    return result;
}

std::string Item::GetName(ITEMS id) noexcept {
    std::string name = "NULL";

    switch (id)
    {
    case ITEMS::HEALTH_POTION:
        name = "Health Potion";
        break;
    
    default:
        break;
    }

    return name;
}
