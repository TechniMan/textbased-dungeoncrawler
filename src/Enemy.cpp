#include "Enemy.hpp"

Enemy::Enemy(std::string& name, int gold, uint attackBonus, uint dodgeBonus, uint hitPoints)
    : Creature(name, hitPoints * 10U),
      m_gold(gold) {
    m_attackSkill = attackBonus * 10U;
    m_dodgeSkill = dodgeBonus * 10U;
}

Enemy::~Enemy() {

}

unsigned int Enemy::GoldWorth() const {
    return m_gold;
}
