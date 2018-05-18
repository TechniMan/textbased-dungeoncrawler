#include "../include/Creature.hpp"
#include <math.h>

Creature::Creature(std::string name, unsigned int maxHp)
    : m_name(name), m_maxHp(maxHp), m_currentHp(maxHp) {

}

Creature::~Creature() {

}

int Creature::AbilityModifier(unsigned int abilityScore) const {
    if (abilityScore >= 10) {
        return (int)floor((abilityScore - 10) * 0.5f);
    }
    return (int)ceil((-10 + abilityScore) * 0.5f);
}

std::string Creature::GetName() const {
    return m_name;
}

bool Creature::IsAlive() const {
    return m_currentHp > 0;
}

bool Creature::Damage(unsigned int damageAmount) {
    if (m_currentHp > damageAmount) {
        m_currentHp -= damageAmount;
        return true;
    }
    m_currentHp = 0;
    return false;
}

void Creature::Heal(unsigned int healAmount) {
    if (healAmount == 0) {
        m_currentHp = m_maxHp;
    }
    else {
        m_currentHp += healAmount;
        if (m_currentHp > m_maxHp) {
            m_currentHp = m_maxHp;
        }
    }
}

float Creature::HPPercentage() const {
    return (float)m_currentHp / (float)m_maxHp;
}

std::string Creature::CurrentHealth() const {
    return std::to_string(m_currentHp) + " / " + std::to_string(m_maxHp);
}

int Creature::AttackDamage() const {
    return AbilityModifier(m_strength);
}

unsigned int Creature::Defense() const {
    return 10;
}
