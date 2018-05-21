#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "../include/Creature.hpp"

class Enemy : public Creature {
    private:
        unsigned int m_gold;
        unsigned int m_exp;

    public:
        Enemy(std::string name, int str, int dex, int con, int gold, int exp);
        ~Enemy();

        unsigned int GoldWorth() const;
        unsigned int ExpWorth() const;

        unsigned int Defense() const override;
};

#endif // _ENEMY_HPP_
