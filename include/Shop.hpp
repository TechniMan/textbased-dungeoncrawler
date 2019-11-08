#ifndef _SHOP_HPP_
#define _SHOP_HPP_

#include <map>

#include "ItemInventory.hpp"

class Shop {
private:
    ItemInventory m_itemInventory;

public:
    Shop(void);
    ~Shop(void);

    void SetInventoryAndPrices(const std::map<ITEMS, uint>& itemsAndPrices) noexcept;
    const ItemInventory& GetInventory(void) const noexcept;
    const uint GetCostOf(ITEMS item) const noexcept;
};

#endif // _SHOP_HPP_
