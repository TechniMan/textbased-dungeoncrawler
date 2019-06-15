#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <map>
#include <string>

#include "Item.hpp"

class Inventory {
private:
    // map of item ID and quantity
    std::map<ITEMS, uint> m_items;
    uint m_capacity;

public:
    Inventory(void);
    ~Inventory(void);

    // Adds quantity of item to inventory. If inventory is full, returns false.
    bool AddItem(ITEMS item, uint quantity = 1);
    // Removes quantity of item from inventory. If inventory didn't contain item, returns false.
    bool RemoveItem(ITEMS item, uint quantity = 1);
    // Returns a string representation of the inventory. itemname:quantity;
    std::string ListItems(void) const noexcept;
};

#endif // _INVENTORY_HPP_
