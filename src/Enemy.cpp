#include "../include/Enemy.hpp"

Enemy::Enemy(std::string name, int str, int dex, int con, int gold, int exp)
    : Creature(name, 10) {
    m_strength = str;
    m_dexterity = dex;
    m_constitution = con;
    m_gold = gold;
    m_exp = exp;
}

Enemy::~Enemy() {

}

unsigned int Enemy::GoldWorth() const {
    return m_gold;
}

unsigned int Enemy::ExpWorth() const {
    return m_exp;
}

unsigned int Enemy::Defense() const {
    return 10 + AbilityModifier(m_dexterity);
}
