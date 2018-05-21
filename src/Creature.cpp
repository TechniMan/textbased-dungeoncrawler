#include "../include/Creature.hpp"
#include <cmath>

Creature::Creature(std::string name, unsigned int baseHp)
    : m_name(name), m_baseHp(baseHp) {
    
}

Creature::~Creature() {

}

int Creature::AbilityModifier(int abilityScore) const {
    return (int)floorf(abilityScore * 0.5f);
}

unsigned int Creature::GetMaximumHp() const {
    return m_baseHp + AbilityModifier(m_constitution);
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
        m_currentHp = GetMaximumHp();
    }
    else {
        m_currentHp += healAmount;
        if (m_currentHp > GetMaximumHp()) {
            m_currentHp = GetMaximumHp();
        }
    }
}

float Creature::HPPercentage() const {
    return (float)m_currentHp / (float)GetMaximumHp();
}

int Creature::AttackBonus() const {
    return AbilityModifier(m_dexterity);
}

int Creature::AttackDamage() const {
    return Max(AbilityModifier(m_strength), 0);
}

unsigned int Creature::Defense() const {
    return 10 + AbilityModifier(m_dexterity);
}

std::string Creature::CurrentHealth() const {
    return std::to_string(m_currentHp) + " / " + std::to_string(GetMaximumHp());
}

// return "{name} - Health: {current} / {max} Str: {str} Dex: {dex} Con: {con}"
std::string Creature::ToString() const {
    return m_name + " - base:" + std::to_string(m_baseHp) + " Health: " + CurrentHealth() + " Str:" + std::to_string(m_strength) + "(" + std::to_string(AbilityModifier(m_strength)) + ") Dex:" + std::to_string(m_dexterity) + "(" + std::to_string(AbilityModifier(m_dexterity)) + ") Con:" + std::to_string(m_constitution) + "(" + std::to_string(AbilityModifier(m_constitution)) + ")";
}
