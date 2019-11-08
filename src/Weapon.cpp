#include "Weapon.hpp"
#include "Utilities.hpp"

WEAPONS Weapon::GetFromName(std::string weaponName) {
    WEAPONS result = WEAPONS::UNARMED;

    std::string low = to_lower(weaponName);
    if (low == "dagger") {
        result = WEAPONS::DAGGER;
    }
    else if (low == "shortsword") {
        result = WEAPONS::SHORTSWORD;
    }
    else if (low == "longsword") {
        result = WEAPONS::LONGSWORD;
    }
    else if (low == "greatsword") {
        result = WEAPONS::GREATSWORD;
    }

    return result;
}

Weapon::Weapon(std::string name, unsigned int minDamage, unsigned int maxDamage)
    : m_name(name), m_minimumDamage(minDamage), m_maximumDamage(maxDamage) {
    
}

std::string Weapon::GetName() const noexcept {
    return m_name;
}

unsigned int Weapon::DamageRange() const noexcept {
    return m_maximumDamage - m_minimumDamage;
}

unsigned int Weapon::GetDamage(pcg32 rng) const {
    return m_minimumDamage + pcg_extras::bounded_rand(rng, DamageRange());
}

std::map<WEAPONS, Weapon> AvailableWeapons = std::map<WEAPONS, Weapon> {
    { WEAPONS::UNARMED, Weapon("Unarmed", 1, 2) }, // 1
    { WEAPONS::DAGGER, Weapon("Dagger", 1, 4) }, // 2
    { WEAPONS::SHORTSWORD, Weapon("Shortsword", 1, 6) }, // 3
    { WEAPONS::LONGSWORD, Weapon("Longsword", 1, 8) }, // 4
    { WEAPONS::GREATSWORD, Weapon("Greatsword", 2, 12) } // 6
};
