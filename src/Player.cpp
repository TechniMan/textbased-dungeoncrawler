#include "../include/Player.hpp"

Player::Player(std::string name, unsigned int maxHp)
    : Creature(name, maxHp) {
    m_strength = 10;
}

Player::~Player() {
    
}

bool Player::Pay(unsigned int goldCost) {
    if (m_gold >= goldCost) {
        m_gold -= goldCost;
        return true;
    }
    return false;
}

bool Player::LevelUp(unsigned int expCost) {
    if (m_exp >= expCost) {
        m_exp -= expCost;
        return true;
    }
    return false;
}

void Player::Reward(unsigned int gold, unsigned int exp) {
    m_gold += gold;
    m_exp += exp;
}

int Player::AttackDamage() const {
    if (4 + Creature::AttackDamage() > 0) {
        return 4 + Creature::AttackDamage();
    }
    return 0;
}

unsigned int Player::Defense() const {
    return Creature::Defense();
}
