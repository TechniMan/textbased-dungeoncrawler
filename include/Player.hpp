#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Creature.hpp"

// stats
//  human average is all 10s: str, dex, con
//  fighter hp: 10 + con mod
//  fighter hp+ per level: (1d10 or 6) + con mod
// armour
//  clothes: AC 10
//  leather armour: AC 11+dexmod
//  chain mail: AC 16, req Str 15
//  shield: AC+2
// weapons
//  dagger: 1d4 damage
//  shortsword: 1d6 damage
//  longsword: 1d8 damage
//  greatsword: 2d6 damage
class Player : public Creature {
    private:
        unsigned int m_gold;
        unsigned int m_exp;

    public:
        Player(std::string name, unsigned int maxHp);
        ~Player();

        bool Pay(unsigned int goldCost);
        bool LevelUp(unsigned int expCost);
        void Reward(unsigned int gold, unsigned int experience);
        int AttackDamage() const override;
        unsigned int Defense() const override;
};

#endif // _PLAYER_HPP_