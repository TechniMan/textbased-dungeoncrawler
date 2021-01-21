#include "Creature.hpp"
#include <cmath>

Creature::Creature(std::string& name, unsigned int toughness)
    : m_name(name),
      m_toughnessSkill(toughness) {
    m_currentHp = GetMaximumHp();
}

Creature::Creature(Creature& creature)
    : m_name(creature.m_name),
      m_toughnessSkill(creature.m_toughnessSkill) {
    m_currentHp = GetMaximumHp();
}

Creature::~Creature() {

}

unsigned int Creature::GetMaximumHp() const {
    return m_toughnessSkill / 10U;
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

std::string Creature::CurrentHealth() const {
    return std::to_string(m_currentHp) + " / " + std::to_string(GetMaximumHp());
}

// return "{name} - Health: {current} / {max}{insert}\nATK: {atk} DDG: {ddg} TUF: {tuf}"
std::string Creature::ToString() const {
    return m_name + " - Health: " + CurrentHealth()
        + "\nATK:" + std::to_string(m_attackSkill) + " DDG:" + std::to_string(m_dodgeSkill)
        + " TUF:" + std::to_string(m_toughnessSkill);
}

uint Creature::GetAttackBonus(void) const noexcept {
    return m_attackSkill / 10U;
}

uint Creature::GetDodgeBonus(void) const noexcept {
    return m_dodgeSkill / 10U;
}

void Creature::ImproveAttackSkill(void) noexcept {
    m_attackSkill++;
}

void Creature::ImproveDodgeSkill(void) noexcept {
    m_dodgeSkill++;
}

bool Creature::TakeDamage(unsigned int damage) noexcept {
    if (damage >= m_currentHp) {
        m_currentHp = 0;
        return false;
    }
    m_currentHp -= damage;
    m_toughnessSkill++;
    return true;
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

const ItemInventory& Creature::GetInventory(void) const noexcept {
    return m_itemInventory;
}
