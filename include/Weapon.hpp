#ifndef _WEAPON_HPP_
#define _WEAPON_HPP_

#include <string>
#include <map>

#include "pcg-random/pcg_random.hpp"

class Weapon {
private:
    std::string m_name;
    unsigned int m_minimumDamage;
    unsigned int m_maximumDamage;

public:
    Weapon(std::string name, unsigned int maxDamage, unsigned int minDamage);
    
    std::string GetName() const noexcept;
    unsigned int DamageRange() const noexcept;
    unsigned int GetDamage(pcg32 rng) const;
};

extern std::map<std::string, Weapon> AvailableWeapons;

#endif //_WEAPON_HPP_
