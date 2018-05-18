#ifndef _CREATURE_HPP_
#define _CREATURE_HPP_

#include <string>

class Creature {
    private:
        std::string m_name;
        unsigned int m_maxHp;
        unsigned int m_currentHp;

    protected:
        unsigned int m_strength;
        
        int AbilityModifier(unsigned int abilityScore) const;

    public:
        Creature(std::string name, unsigned int maxHp);
        ~Creature();

        std::string GetName() const;
        bool IsAlive() const;

        // Restore hp to the creature.
        void Heal(unsigned int healAmount);

        // Deal damage to this creature. Returns false if the creature dies.
        bool Damage(unsigned int damageAmount);

        // Returns between 0.0f and 1.0f
        float HPPercentage() const;

        // returns "{current} / {max}"
        std::string CurrentHealth() const;

        // returns the creature's attack damage
        virtual int AttackDamage() const;

        // returns the creature's defense value
        virtual unsigned int Defense() const;
};

#endif // _CREATURE_HPP_
