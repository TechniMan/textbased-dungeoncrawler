#include "Shop.hpp"

Shop::Shop(void)
    : m_itemInventory(ItemInventory()) {

}

Shop::~Shop(void) {

}

void Shop::SetInventoryAndPrices(const std::map<ITEMS, uint>& itemsAndPrices) noexcept {
    m_itemInventory.Clear();
    for (auto itemAndPrice : itemsAndPrices) {
        m_itemInventory.AddItem(itemAndPrice.first, itemAndPrice.second);
    }
}

const ItemInventory& Shop::GetInventory(void) const noexcept {
    return m_itemInventory;
}

const uint Shop::GetCostOf(ITEMS item) const noexcept {
    auto items = m_itemInventory.GetItems();
    if (items.count(item) == 1)
    {
        return items[item];
    }
    return 0;
}
