#ifndef _CREATURE_HPP_
#define _CREATURE_HPP_

#include <string>
#include "pcg-random/pcg_random.hpp"

#include "Item.hpp"
#include "ItemInventory.hpp"
#include "Utilities.hpp"
#include "Weapon.hpp"

class Creature {
protected:
    // creature's name
    std::string m_name;
    // current hit point value
    unsigned int m_currentHp;

    // attributes
    unsigned int m_attackSkill;
    unsigned int m_dodgeSkill;
    unsigned int m_toughnessSkill;

    // derive maximum hp from stats
    unsigned int GetMaximumHp() const;

    // inventory of consumable items
    ItemInventory m_itemInventory;

public:
    Creature(std::string& name, unsigned int baseHp);
    Creature(Creature& creature);
    ~Creature();

    std::string GetName() const;


    /// Combat

    bool IsAlive() const;
    // Deal damage to this creature. Returns false if the creature dies.
    bool Damage(unsigned int damageAmount);
    // Restore hp to the creature.
    void Heal(unsigned int healAmount);
    // Returns between 0.0f and 1.0f
    float HPPercentage() const;
    // returns "{current} / {max}"
    std::string CurrentHealth() const;
    // return "{name} - Health: {current} / {max} Str: {str} Dex: {dex} Con: {con}"
    virtual std::string ToString() const;

    uint GetAttackBonus() const noexcept;
    uint GetDodgeBonus() const noexcept;
    void ImproveAttackSkill() noexcept;
    void ImproveDodgeSkill() noexcept;
    // true: Still alive. false: Not alive; game over.
    bool TakeDamage(unsigned int damage) noexcept;


    /// Inventory
    
    // Use item
    bool UseItem(ITEMS item, Creature& target) noexcept;
    // Give the creature quantity of item
    bool Give(ITEMS item, unsigned int quantity = 1);
    // Make the creature discard quantity of item
    bool Discard(ITEMS item, unsigned int quantity = 1);
    // Make the creature consume (use & discard) 1 of item
    bool Consume(ITEMS item, Creature& opponent, unsigned int quantity = 1);
    const ItemInventory& GetInventory(void) const noexcept;
};

#endif // _CREATURE_HPP_
