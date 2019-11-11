#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <string>
#include <iostream>

#include "ItemInventory.hpp"
#include "GAMESTATE.hpp"

class Logger {
private:
    //std::ostream m_outStream;
    static const std::string Blue;
    static const std::string Cyan;
    static const std::string Gray;
    static const std::string Green;
    static const std::string Purple;
    static const std::string Red;
    static const std::string Reset;
    static const std::string White;
    static const std::string Yellow;

public:
    Logger();
    ~Logger();

    static const std::string ResetColour;
    static const std::string BadColour;
    static const std::string CommandColour;
    static const std::string ItemColour;
    static const std::string MagicColour;
    static const std::string NameColour;
    static const std::string SuccessColour;

    void Write(std::string out) const noexcept;
    void WriteLine(std::string outLine = "") const noexcept;
    void WriteError(std::string errorMessage) const noexcept;
    void WriteCommandDescription(std::string commandName, std::string commandDescription) const noexcept;
    void WriteCommandNotFound(std::string unknownCommand) const noexcept;
    void WriteHelp(GAMESTATE gameState) const noexcept;
    void WriteItem(const std::pair<ITEMS, unsigned int>& item) const noexcept;
    void WriteInventory(const ItemInventory& inventory) const noexcept;
};

#endif // _LOGGER_HPP_
