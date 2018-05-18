#include "../include/Enemy.hpp"

Enemy::Enemy(std::string name, unsigned int maxHp)
    : Creature(name, maxHp) {
    
}

Enemy::~Enemy() {

}

unsigned int Enemy::GoldWorth() const {
    return m_gold;
}

unsigned int Enemy::ExpWorth() const {
    return m_exp;
}

int Enemy::AttackDamage() const {
    return Creature::AttackDamage();
}

unsigned int Enemy::Defense() const {
    return Creature::Defense();
}
