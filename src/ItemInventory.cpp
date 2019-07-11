#include "ItemInventory.hpp"
#include <string.h>

ItemInventory::ItemInventory(void) {
    m_capacity = 10U;
    m_items = std::map<ITEMS, unsigned int>();
}

ItemInventory::~ItemInventory(void) {
    m_items.clear();
}

bool ItemInventory::AddItem(ITEMS itemId, unsigned int quantity) {
    bool itemAdded = false;
    // IF object is in inventory already
    if (m_items.find(itemId) != m_items.end()) {
        m_items[itemId] += quantity;
        itemAdded = true;
    }
    // ELSE IF inventory not full
    else if (m_items.size() < m_capacity) {
        m_items[itemId] = quantity;
        itemAdded = true;
    }
    return itemAdded;
}

bool ItemInventory::RemoveItem(ITEMS itemId, unsigned int quantity) {
    bool itemRemoved = false;
    if (m_items.find(itemId) != m_items.end()) {
        m_items[itemId] -= quantity;
        if ((int)m_items[itemId] - (int)quantity < 1) {
            m_items.erase(itemId);
        }
        itemRemoved = true;
    }
    return itemRemoved;
}

void ItemInventory::Clear(void) noexcept {
    m_items.clear();
}

const std::map<ITEMS, unsigned int>& ItemInventory::GetItems(void) const noexcept {
    return m_items;
}

nlohmann::json ItemInventory::Serialise(void) const noexcept {
    nlohmann::json cereal;
    cereal["capacity"] = m_capacity;
    cereal["stack_size"] = m_stackSize;
    cereal["items"] = m_items;
    return cereal;
}

ItemInventory ItemInventory::Deserialise(nlohmann::json cereal) {
    auto result = ItemInventory();

    result.m_capacity = cereal["capacity"];
    result.m_stackSize = cereal["stack_size"];
    result.m_items = cereal["items"].get<std::map<ITEMS, unsigned int>>();

    return result;
}
