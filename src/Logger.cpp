#include "Logger.hpp"

Logger::Logger() {
}

Logger::~Logger() {
}

void Logger::Write(std::string out) const {
    std::cout << out;
}

void Logger::WriteLine(std::string outLine) const {
    std::cout << outLine << std::endl;
}

void Logger::WriteError(std::string errorMessage) const {
    WriteLine("The game has encountered an error: " + errorMessage + "! Please send this message to the developer, and tell them what you were doing beforehand. You can find contact details with the 'about' command at the main menu. Thank you! <3");
}

void Logger::WriteCommandNotFound(std::string unknownCommand) const {
    WriteLine("I'm afraid that " + unknownCommand + " is not a valid command; try 'help'. Sorry!");
}

void Logger::WriteHelp(GAMESTATE gameState) const {
    WriteLine("Available commands are:");
    
    switch (gameState)
    {
        case GAMESTATE::MENU:
            WriteLine("new <name>:  start a new game (with name [name])");
            WriteLine("load <name>: load an existing game with name <name>");
            //WriteLine("contact: print contact details for the developer (hello! we're friendly!)");
            WriteLine("about:       show general information about the game; who developed it and why");
            // exit: exit the game
            break;

        case GAMESTATE::TOWN:
            WriteLine("rest:              restore your health, heal your wounds, and save the game");
            WriteLine("travel:            go out in search of adventure and danger");
            WriteLine("status:            show info about you");
            WriteLine("levelup <ability>: attempt to increase your <ability> score by spending exp");
            WriteLine("inventory:         list your inventory");
            // shop inventory: list shop stock
            // shop buy <item>: attempt to buy <item>
            // shop sell <item>: sell <item>
            // don <equipment>: attempt to don <equipment>
            // doff <equipment>: attempt to doff <equipment>
            // quit: quit to the menu (alias: exit)
            break;

        case GAMESTATE::COMBAT:
            WriteLine("attack: hit the damn thig with your pointy stick");
            //WriteLine("cast <spell>: cast <spell> at the target");
            //WriteLine("consume <item>: verb a consumable item");
            WriteLine("status: show your & your opponent's info");
            WriteLine("run:    attempt to flee from your opponent");
            break;

        default:
            break;
    }

    WriteLine("help: this handy help message :)");
    WriteLine("exit: quit the game");
}
