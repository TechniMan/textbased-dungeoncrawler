#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Creature.hpp"

class Enemy : public Creature {
    private:
        unsigned int m_gold;
        unsigned int m_exp;

    public:
        Enemy(std::string& name, Weapon& weapon, int str, int dex, int con, int gold, int exp);
        ~Enemy();

        unsigned int GoldWorth() const;
        unsigned int ExpWorth() const;
};

#endif // _ENEMY_HPP_
