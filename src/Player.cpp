#include "../include/Player.hpp"

Player::Player(std::string name)
    : Creature(name, 10) {
    m_strength = 2;
    m_dexterity = 2;
    m_constitution = 2;
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

bool Player::LevelUp(CREATURE_ABILITIES ability) {
    if (m_exp >= LEVELUP_COST) {
        switch (ability) {
            case CREATURE_ABILITIES_STRENGTH: m_strength++; break;
            case CREATURE_ABILITIES_DEXTERITY: m_dexterity++; break;
            case CREATURE_ABILITIES_CONSTITUTION: m_constitution++; break;
            default: break;
        }
        m_exp -= LEVELUP_COST;
        return true;
    }
    return false;
}

void Player::Reward(unsigned int gold, unsigned int exp) {
    m_gold += gold;
    m_exp += exp;
}

int Player::AttackBonus() const {
    return Creature::AttackBonus();
}

int Player::AttackDamage() const {
    return Max(AbilityModifier(m_strength) + 4, 0);
}

unsigned int Player::Defense() const {
    return Creature::Defense();
}
