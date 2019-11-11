#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Creature.hpp"

class Player : public Creature {
private:
    unsigned int m_gold;
    unsigned int m_attackSkill;
    unsigned int m_blockSkill;
    unsigned int m_dodgeSkill;
    unsigned int m_parrySkill;
    unsigned int m_toughnessSkill;

    Weapon m_weapon;

public:
    static bool Load(std::string filename, Player& player);
    bool Save(std::string filename);

    Player(std::string& name);
    ~Player();

    // true: Succeeded. false: Failed and levelled up.
    bool TestAttack(unsigned int rollValue) noexcept;
    // true: Succeeded. false: Failed and levelled up.
    bool TestBlock(unsigned int rollValue) noexcept;
    // true: Succeeded. false: Failed and levelled up.
    bool TestDodge(unsigned int rollValue) noexcept;
    // 1: Succeeded. 0: Matched skill level, so riposte. -1: Failed and levelled up.
    int TestParry(unsigned int rollValue) noexcept;
    // true: Took the damage and survived. false: Couldn't take the damage; dead.
    bool TakeDamage(unsigned int damage = 1) noexcept;

    // true: Able to pay, cost has been taken from wallet. false: Unable to pay, cost not taken.
    bool Pay(unsigned int goldCost);
    // Give specified amounts of gold to player.
    void Reward(unsigned int gold);
    virtual std::string ToString() const override;
};

#endif // _PLAYER_HPP_
