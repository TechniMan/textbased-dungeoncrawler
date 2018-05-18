#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "../include/Creature.hpp"

class Enemy : public Creature {
    private:
        unsigned int m_gold;
        unsigned int m_exp;

    public:
        Enemy(std::string name, unsigned int maxHp);
        ~Enemy();

        unsigned int GoldWorth() const;
        unsigned int ExpWorth() const;

        int AttackDamage() const override;
        unsigned int Defense() const override;
};

#endif // _ENEMY_HPP_
