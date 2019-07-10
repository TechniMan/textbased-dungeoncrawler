#ifndef _ITEMS_HPP_
#define _ITEMS_HPP_

#include <string>
#include <vector>

enum class ITEMS {
    NULL_ITEM,
    HEALTH_POTION
};

namespace Item {
    ITEMS GetByName(std::string name) noexcept;
    std::string GetName(ITEMS item) noexcept;
};

#endif // _ITEMS_HPP_
