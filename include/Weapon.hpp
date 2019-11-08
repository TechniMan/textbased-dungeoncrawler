#ifndef _WEAPON_HPP_
#define _WEAPON_HPP_

#include <string>
#include <map>

#include "pcg-random/pcg_random.hpp"

enum class WEAPONS {
    UNARMED,
    DAGGER,
    SHORTSWORD,
    LONGSWORD,
    GREATSWORD
};

class Weapon {
private:
    std::string m_name;
    unsigned int m_minimumDamage;
    unsigned int m_maximumDamage;

public:
    static WEAPONS GetFromName(std::string weaponName);

    Weapon(std::string name, unsigned int minDamage, unsigned int maxDamage);
    
    std::string GetName() const noexcept;
    unsigned int DamageRange() const noexcept;
    unsigned int GetDamage(pcg32 rng) const;
};

extern std::map<WEAPONS, Weapon> AvailableWeapons;

#endif // _WEAPON_HPP_
