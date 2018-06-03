#include "../include/Weapon.hpp"

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

std::map<std::string, Weapon> AvailableWeapons = std::map<std::string, Weapon> {
    { "Unarmed", Weapon("Unarmed", 0, 1) },
    { "Dagger", Weapon("Dagger", 1, 4) },
    { "Shortsword", Weapon("Shortsword", 1, 6) },
    { "Longsword", Weapon("Longsword", 1, 8) },
    { "Greatsword", Weapon("Greatsword", 2, 12) }
};
