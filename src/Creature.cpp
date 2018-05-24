#include "../include/Creature.hpp"
#include <cmath>

Creature::Creature(std::string name, unsigned int baseHp)
    : m_name(name), m_baseHp(baseHp) {
    
}

Creature::~Creature() {

}

int Creature::AbilityModifier(int abilityScore) const {
    // diminishing returns: earlier increases are more significant, but later increases are less likely to improve the stat
    return (int)ceil(pow((double)abilityScore, 0.92));
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
    int strMod = AbilityModifier(m_strength);
    std::string strModStr = std::to_string(strMod);
    if (strMod > 0) { strModStr = "+" + strModStr; }
    int dexMod = AbilityModifier(m_dexterity);
    std::string dexModStr = std::to_string(dexMod);
    if (dexMod > 0) { dexModStr = "+" + dexModStr; }
    int conMod = AbilityModifier(m_constitution);
    std::string conModStr = std::to_string(conMod);
    if (conMod > 0) { conModStr = "+" + conModStr; }

    return m_name + " - Health: " + CurrentHealth() + " | Str:" + std::to_string(m_strength) + "(" + strModStr + ") | Dex:" + std::to_string(m_dexterity) + "(" + dexModStr + ") | Con:" + std::to_string(m_constitution) + "(" + conModStr + ")";
}
