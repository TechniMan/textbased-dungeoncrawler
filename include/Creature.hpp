#ifndef _CREATURE_HPP_
#define _CREATURE_HPP_

#include <string>
#include "pcg-random/pcg_random.hpp"

#include "Item.hpp"
#include "ItemInventory.hpp"
#include "Utilities.hpp"
#include "Weapon.hpp"

enum CREATURE_ABILITIES {
    CREATURE_ABILITIES_STRENGTH,
    CREATURE_ABILITIES_DEXTERITY,
    CREATURE_ABILITIES_CONSTITUTION
};

class Creature {
protected:
    // creature's name
    std::string m_name;
    // creature's base hit points
    unsigned int m_baseHp;
    // current hit point value
    unsigned int m_currentHp;
    // affects attack damage
    int m_strength;
    // affects chance to dodge & chance for extra attack(s)
    int m_dexterity;
    // affects maximum hp
    int m_constitution;
    // weapon
    Weapon m_weapon;
    
    // get the modifier value for an ability score
    int AbilityModifier(int abilityScore) const;
    // derive maximum hp from stats
    unsigned int GetMaximumHp() const;

    // inventory of consumable items
    ItemInventory m_itemInventory;

public:
    Creature(std::string& name, unsigned int baseHp, Weapon& weapon);
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
    // the creature's bonus to hit rolls (dex bonus)
    int AttackBonus() const;
    // the creature's attack damage (weapon dmg + str bonus)
    int AttackDamage(pcg32 rng) const;
    // the creature's defense value (10 + dex bonus)
    unsigned int Defense() const;
    // returns "{current} / {max}"
    std::string CurrentHealth() const;
    // return "{name} - Health: {current} / {max} Str: {str} Dex: {dex} Con: {con}"
    virtual std::string ToString() const;


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
