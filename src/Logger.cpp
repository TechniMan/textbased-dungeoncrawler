#include "Logger.hpp"
#include <iomanip>

const std::string Logger::Gray   = "\x1b[30m";
const std::string Logger::Red    = "\x1b[31m";
const std::string Logger::Green  = "\x1b[32m";
const std::string Logger::Yellow = "\x1b[33m";
const std::string Logger::Blue   = "\x1b[34m";
const std::string Logger::Purple = "\x1b[35m";
const std::string Logger::Cyan   = "\x1b[36m";
const std::string Logger::White  = "\x1b[37m";
const std::string Logger::Reset  = "\x1b[39m";

Logger::Logger() {
}

Logger::~Logger() {
}

const std::string Logger::ResetColour   = White;
const std::string Logger::BadColour     = Red;
const std::string Logger::CommandColour = Blue;
const std::string Logger::ItemColour    = Yellow;
const std::string Logger::MagicColour   = Purple;
const std::string Logger::NameColour    = Cyan;
const std::string Logger::SuccessColour = Green;

void Logger::Write(std::string out) const noexcept {
    std::cout << out;
}

void Logger::WriteLine(std::string outLine) const noexcept {
    std::cout << outLine << std::endl;
}

void Logger::WriteError(std::string errorCode) const noexcept {
    WriteLine(BadColour);
    WriteLine("The game has encountered an error: " + errorCode + "! Please send this message to the developer, and tell them what you were doing beforehand. You can find contact details with the 'about' command at the main menu. Thank you! <3");
    WriteLine(ResetColour);
}

void Logger::WriteCommandDescription(std::string commandName, std::string commandDescription) const noexcept {
    std::cout << CommandColour << std::setw(20) << std::left << std::setfill(' ') << commandName
              << ResetColour << std::setw(60) << commandDescription << std::endl;
}

void Logger::WriteCommandNotFound(std::string unknownCommand) const noexcept {
    WriteLine("I'm afraid that " + unknownCommand + " is not a valid command; try 'help'. Sorry!");
}

void Logger::WriteHelp(GAMESTATE gameState) const noexcept {
    WriteLine("Available commands are:");
    
    switch (gameState)
    {
        case GAMESTATE::MENU:
            WriteCommandDescription("new <name>", "start a new game (with name <name>)");
            WriteCommandDescription("load <name>", "load an existing game with name <name>");
            WriteCommandDescription("about", "show general information about the game; who developed it and why");
            //WriteCommandDescription("contact", "print contact details for the developer (hello! I'm friendly!)");
            break;

        case GAMESTATE::TOWN:
            WriteCommandDescription("rest", "restore your health, heal your wounds, and save the game");
            WriteCommandDescription("travel", "go out in search of adventure and danger");
            WriteCommandDescription("status", "show info about you");
            WriteCommandDescription("levelup <ability>", "attempt to increase your <ability> score by spending exp");
            WriteCommandDescription("inventory", "list your inventory");
            WriteCommandDescription("shop inventory", "list shop inventory and prices");
            WriteCommandDescription("shop buy <item>", "attempt to buy <item>");
            //WriteCommandDescription("shop sell <item>", "sell <item>");
            //WriteCommandDescription("don <equipment>", "attempt to don <equipment>");
            //WriteCommandDescription("doff <equipment>", "attempt to doff <equipment>");
            //WriteCommandDescription("quit", "quit to the menu");
            break;

        case GAMESTATE::COMBAT:
            WriteCommandDescription("attack", "hit the damn thing");
            //WriteCommandDescription("cast <spell>", "cast <spell> at the target");
            WriteCommandDescription("consume <item>", "consume a consumable item");
            WriteCommandDescription("status", "show your & your opponent's info");
            WriteCommandDescription("run", "attempt to flee back to town");
            break;

        default:
            break;
    }

    WriteCommandDescription("help", "this handy help message :)");
    WriteCommandDescription("exit", "close the game");
}

void Logger::WriteItem(const std::pair<ITEMS, unsigned int>& item) const noexcept {
    std::cout << ItemColour << std::setw(32) << std::left << std::setfill('.') << Item::GetName(item.first)
              << ResetColour << std::setw(5) << std::right << std::setfill('.') << std::to_string(item.second)
              << std::endl;
}

void Logger::WriteInventory(const ItemInventory& inventory) const noexcept {
    auto items = inventory.GetItems();
    for (auto item : items) {
        WriteItem(item);
    }
}
