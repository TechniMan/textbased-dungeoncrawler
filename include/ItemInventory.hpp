#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <map>
#include <string>

#include "nlohmann/json.hpp"
#include "Item.hpp"

class ItemInventory {
private:
    // map of object ID and quantity
    std::map<ITEMS, unsigned int> m_items;
    unsigned int m_capacity;
    unsigned int m_stackSize;

public:
    ItemInventory(void);
    ~ItemInventory(void);

    // Adds quantity of item to inventory. If inventory is full, returns false.
    bool AddItem(ITEMS itemId, unsigned int quantity = 1);
    // Removes quantity of item from inventory. If inventory didn't contain item, returns false.
    bool RemoveItem(ITEMS itemId, unsigned int quantity = 1);
    // Clear the inventory
    void Clear(void) noexcept;
    // Returns a string representation of the inventory. itemname:quantity;
    const std::map<ITEMS, unsigned int>& GetItems(void) const noexcept;
    // For saving
    nlohmann::json Serialise(void) const noexcept;
    // For loading
    static ItemInventory Deserialise(nlohmann::json serialised);
};

#endif // _INVENTORY_HPP_
