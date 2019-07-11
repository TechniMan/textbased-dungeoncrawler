#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <string>
#include <iostream>

#include "ItemInventory.hpp"
#include "GAMESTATE.hpp"

class Logger {
private:
    //std::ostream m_outStream;

public:
    Logger();
    ~Logger();

    void Write(std::string out) const noexcept;
    void WriteLine(std::string outLine = "") const noexcept;
    void WriteError(std::string errorMessage) const noexcept;
    void WriteCommandNotFound(std::string unknownCommand) const noexcept;
    void WriteHelp(GAMESTATE gameState) const noexcept;
    void WriteItem(const std::pair<ITEMS, unsigned int>& item) const noexcept;
    void WriteInventory(const ItemInventory& inventory) const noexcept;
};

#endif // _LOGGER_HPP_
