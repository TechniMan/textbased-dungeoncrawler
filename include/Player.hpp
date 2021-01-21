#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Creature.hpp"

class Player : public Creature {
private:
    unsigned int m_gold;

    Weapon m_weapon;

public:
    static bool Load(std::string filename, Player& player);
    bool Save(std::string filename);

    Player(std::string& name);
    ~Player();

    // true: Able to pay, cost has been taken from wallet. false: Unable to pay, cost not taken.
    bool Pay(unsigned int goldCost);
    // Give specified amounts of gold to player.
    void Reward(unsigned int gold);
    // insert is ignored
    virtual std::string ToString() const override;
};

#endif // _PLAYER_HPP_
