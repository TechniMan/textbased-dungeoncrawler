#include "Item.hpp"
#include "Utilities.hpp"

Item::Item(uint itemId, std::string itemName)
    : id(itemId), name(itemName) {
    
}

Item::Item(const Item& other) {
    id = other.id;
    name = other.name;
}

std::string Item::ToString(void) const noexcept {
    return "id: " + std::to_string(id) + ", " + name;
}

bool Item::UseItem(Items item, Creature& user, Creature& target) noexcept {
    bool result = true;

    switch (item)
    {
    case ITEM_HEALTH_POTION:
        user.Heal(20U);
        break;
    
    case ITEM_NULL:
    default:
        result = false;
        break;
    }

    return result;
}

Item Item::GetByName(std::string name) noexcept {
    Item item = Item(ITEM_NULL, "NULL");

    if (to_lower(name) == "health potion") {
        item.id = ITEM_HEALTH_POTION;
        item.name = "Health Potion";
    }

    return item;
}
