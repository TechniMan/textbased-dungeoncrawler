#include "Enemy.hpp"

Enemy::Enemy(std::string& name, int health, int gold)
    : Creature(name, health) {
    m_gold = gold;
}

Enemy::~Enemy() {

}

unsigned int Enemy::GoldWorth() const {
    return m_gold;
}
