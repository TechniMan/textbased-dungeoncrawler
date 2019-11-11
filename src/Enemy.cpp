#include "Enemy.hpp"

Enemy::Enemy(std::string& name, int gold)
    : Creature(name, 10) {
    m_gold = gold;
}

Enemy::~Enemy() {

}

unsigned int Enemy::GoldWorth() const {
    return m_gold;
}
