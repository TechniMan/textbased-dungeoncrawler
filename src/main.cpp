#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

#include "Game.hpp"

// arguments are ignored lol
int main(int argc, char ** args) {
    Logger * logger = new Logger();
    Game * game = new Game();

    // intro
    logger->Write("\x1b[1m");
    logger->WriteLine("A text-based dungeon-crawling game, made by Will Thomas @techniman");
    logger->WriteLine("Made from scratch using straight-forward C++: https://github.com/techniman/textbased-dungeoncrawler");
    logger->WriteLine("Still in development, so if anything breaks, please let me know (or fix it)! Cheers, and enjoy!");
    logger->WriteLine();
    logger->WriteLine("Menu: From here, you can start a {new} game, {load} another character, or {exit}! At any time, {help} will tell you the available commands.");
    
    // begin game loop
    std::string lineIn;
    logger->Write("\n> ");
    while (std::getline(std::cin, lineIn)) {
        if (lineIn.size() > 0) {
            std::vector<std::string> input = split(lineIn, ' ');
            std::string command = input.at(0);
            std::string mainArg;
            std::string fullArg;
            if (input.size() > 1) {
                mainArg = input.at(1);
                fullArg = lineIn.substr(command.length() + 1, std::string::npos);
            }
            
            // if ProcessCommand returns false, then quit the game
            if (!game->ProcessCommand(command, mainArg, fullArg)) {
                break;
            }
        }

        // begin the next line to prompt user input
        logger->Write("\n> ");
    }

    return 0;
}
