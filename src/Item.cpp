#include "Item.hpp"
#include "Utilities.hpp"

bool Item::UseItem(ITEMS item, Creature& user, Creature& target) noexcept {
    bool result = true;

    switch (item)
    {
    case ITEM_HEALTH_POTION:
        user.Heal(20U);
        break;
    
    default:
        result = false;
        break;
    }

    return result;
}

ITEMS Item::GetByName(std::string name) noexcept {
    ITEMS result = ITEM_NULL;

    if (to_lower(name) == "health potion") {
        result = ITEM_HEALTH_POTION;
    }
    
    return result;
}

std::string Item::GetName(ITEMS id) noexcept {
    std::string name = "NULL";

    switch (id)
    {
    case ITEM_HEALTH_POTION:
        name = "Health Potion";
        break;
    
    default:
        break;
    }

    return name;
}
