#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "pcg-random/pcg_random.hpp"
#include "pcg-random/pcg_extras.hpp"

#include "Player.hpp"
#include "Enemy.hpp"
#include "Logger.hpp"
#include "GAMESTATE.hpp"

class Game {
    private:
        Logger * m_logger = nullptr;
        pcg32 m_rng;

        unsigned int m_gameState = GAMESTATE_MENU;
        unsigned int m_adventureDepth = 0;
        Player * m_player = nullptr;
        Enemy * m_enemy = nullptr;

        void InitialiseCombat();
        void EndCombat();
        void TransitionState(GAMESTATE stateTo);

    public:
        Game();
        ~Game();

        bool ProcessCommand(std::string command, std::string mainArg, std::string fullArg);
};

#endif // _GAME_HPP_
