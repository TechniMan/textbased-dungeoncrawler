#include "Inventory.hpp"

Inventory::Inventory(void) {
    m_capacity = 10U;
    m_items = std::map<ITEMS, uint>();
}

Inventory::~Inventory(void) {
    m_items.clear();
}

bool Inventory::AddItem(ITEMS item, uint quantity) {
    bool itemAdded = false;
    // IF item is in inventory already
    if (m_items.find(item) != m_items.end()) {
        m_items[item] += quantity;
        itemAdded = true;
    }
    // ELSE IF inventory not full
    else if (m_items.size() < m_capacity) {
        m_items[item] = quantity;
        itemAdded = true;
    }
    return itemAdded;
}

bool Inventory::RemoveItem(ITEMS item, uint quantity) {
    bool itemRemoved = false;
    if (m_items.find(item) != m_items.end()) {
        m_items[item] -= quantity;
        if ((int)m_items[item] - (int)quantity < 1) {
            m_items.erase(item);
        }
        itemRemoved = true;
    }
    return itemRemoved;
}

std::string Inventory::ListItems(void) const noexcept {
    std::string result = "";
    for (auto item : m_items) {
        result += Item::GetName(item.first) + ":"
             + std::to_string(item.second) + "; ";
    }
    return result;
}
