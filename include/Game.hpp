#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Player.hpp"
#include "Enemy.hpp"
#include "Logger.hpp"
#include "GAMESTATE.hpp"

// Bit of a blob class, but we remove some of its functionality
//  that makes sense to take out into other classes.
class Game {
    private:
        Logger * m_logger = nullptr;

        unsigned int m_gameState = GAMESTATE_MENU;
        unsigned int m_adventureDepth = 0;
        Player * m_player = nullptr;
        Enemy * m_enemy = nullptr;

        void InitialiseCombat();
        void EndCombat();

    public:
        Game();
        ~Game();

        bool ProcessCommand(std::string command, std::string mainArg, std::string fullArg);
};

#endif // _GAME_HPP_
