#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Creature.hpp"
#include "Inventory.hpp"

class Player : public Creature {
private:
    unsigned int m_level;
    unsigned int m_gold;
    unsigned int m_exp;

    Inventory m_inventory;

public:
    static bool Load(std::string filename, Player& player);
    bool Save(std::string filename);

    Player(std::string& name);
    ~Player();

    bool Pay(unsigned int goldCost);
    unsigned int LevelUpCost() const;
    bool LevelUp(CREATURE_ABILITIES ability);
    void Reward(unsigned int gold, unsigned int experience);
    virtual std::string ToString() const override;

    bool Give(ITEMS item, uint quantity = 1);
    bool Discard(ITEMS item, uint quantity = 1);
    bool Consume(ITEMS item, Creature& opponent, uint quantity = 1);
};

#endif // _PLAYER_HPP_
