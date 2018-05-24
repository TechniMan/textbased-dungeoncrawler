#include "../include/Player.hpp"

#include <fstream>
#include "../include/nlohmann/json.hpp"
using json = nlohmann::json;

bool Player::Load(std::string filename, Player & player) {
    // read from file
    std::ifstream fileIn(filename);
    if (!fileIn) {
        return false;
    }

    json jIn;
    fileIn >> jIn;
    fileIn.close();
    if (!jIn.is_object()) {
        return false;
    }
    
    // deserialise into {player}
    player.m_baseHp = 10;
    player.m_strength = jIn["strength"];
    player.m_dexterity = jIn["dexterity"];
    player.m_constitution = jIn["constitution"];
    player.m_level = jIn["level"];
    player.m_gold = jIn["gold"];
    player.m_exp = jIn["experience"];
    player.m_currentHp = player.GetMaximumHp();
    
    return true;
}

bool Player::Save(std::string filename) {
    // serialise to json
    json player;
    player["strength"] = m_strength;
    player["dexterity"] = m_dexterity;
    player["constitution"] = m_constitution;
    player["level"] = m_level;
    player["gold"] = m_gold;
    player["experience"] = m_exp;

    // write to file
    std::ofstream fileOut(filename);
    if (!fileOut) {
        return false;
    }
    fileOut << std::setw(2) << player << std::endl;
    fileOut.close();

    return true;
}

Player::Player(std::string name)
    : Creature(name, 10) {
    m_strength = 2;
    m_dexterity = 2;
    m_constitution = 2;
}

Player::~Player() {
    
}

bool Player::Pay(unsigned int goldCost) {
    if (m_gold >= goldCost) {
        m_gold -= goldCost;
        return true;
    }
    return false;
}

unsigned int Player::LevelUpCost() {
    // gets gradually more expensive
    return 10u + pow((double)m_level, 1.1);
}

bool Player::LevelUp(CREATURE_ABILITIES ability) {
    if (m_exp >= LevelUpCost()) {
        switch (ability) {
            case CREATURE_ABILITIES_STRENGTH: m_strength++; break;
            case CREATURE_ABILITIES_DEXTERITY: m_dexterity++; break;
            case CREATURE_ABILITIES_CONSTITUTION: m_constitution++; break;
            default: break;
        }
        m_exp -= LevelUpCost();
        m_level++;
        return true;
    }
    return false;
}

void Player::Reward(unsigned int gold, unsigned int exp) {
    m_gold += gold;
    m_exp += exp;
}

int Player::AttackBonus() const {
    return Creature::AttackBonus();
}

int Player::AttackDamage() const {
    return Max(AbilityModifier(m_strength) + 4, 0);
}

unsigned int Player::Defense() const {
    return Creature::Defense();
}

std::string Player::ToString() const {
    return Creature::ToString() + " | Level: " + std::to_string(m_level) + " | Gold: " + std::to_string(m_gold) + "g | Exp: " + std::to_string(m_exp);
}
