#include "Creature.hpp"
#include <cmath>

Creature::Creature(std::string& name, unsigned int baseHp, Weapon& weapon)
    : m_name(name), m_baseHp(baseHp), m_weapon(weapon) {
    
}

Creature::Creature(Creature& creature)
    : m_name(creature.m_name), m_baseHp(creature.m_baseHp), m_weapon(creature.m_weapon) {
    
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



/// Combat

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

int Creature::AttackDamage(pcg32 rng) const {
    return Max(m_weapon.GetDamage(rng) + AbilityModifier(m_strength), 0);
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

    return m_name + " - Health: " + CurrentHealth() + " | Str:" + std::to_string(m_strength) + "(" + strModStr + ") | Dex:" + std::to_string(m_dexterity) + "(" + dexModStr + ") | Con:" + std::to_string(m_constitution) + "(" + conModStr + ")" + " | Weapon: " + m_weapon.GetName();
}



/// Inventory

bool Creature::UseItem(ITEMS item, Creature& target) noexcept {
    bool result = true;

    switch (item)
    {
    case ITEMS::HEALTH_POTION:
        Heal(20U);
        break;
    
    default:
        result = false;
        break;
    }

    return result;
}

bool Creature::Give(ITEMS item, unsigned int quantity) {
    return m_itemInventory.AddItem(item, quantity);
}

bool Creature::Discard(ITEMS item, unsigned int quantity) {
    return m_itemInventory.RemoveItem(item, quantity);
}

bool Creature::Consume(ITEMS item, Creature& opponent, unsigned int quantity) {
    if (m_itemInventory.RemoveItem(item, quantity)) {
        return UseItem(item, opponent);
    }
    return false;
}

std::string Creature::GetInventoryList(void) const noexcept {
    return m_itemInventory.ListItems();
}
