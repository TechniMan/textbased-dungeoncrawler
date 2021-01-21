#include "Player.hpp"

#include <iomanip> // std::setw
#include <fstream>
#include "nlohmann/json.hpp"

bool Player::Load(std::string filename, Player& player) {
    // read from file
    std::ifstream fileIn(filename);
    if (!fileIn) {
        return false;
    }

    nlohmann::json jIn;
    fileIn >> jIn;
    fileIn.close();
    if (!jIn.is_object()) {
        return false;
    }
    
    // deserialise into {player}
    player.m_gold = jIn["gold"];
    player.m_attackSkill = jIn["attack"];
    player.m_dodgeSkill = jIn["dodge"];
    player.m_toughnessSkill = jIn["toughness"];
    player.m_currentHp = player.GetMaximumHp();
    player.m_weapon = AvailableWeapons.at(Weapon::GetFromName(jIn["weapon"]));
    player.m_itemInventory = ItemInventory::Deserialise(jIn["inventory"]);
    
    return true;
}

bool Player::Save(std::string filename) {
    // serialise to json
    nlohmann::json jOut;
    jOut["gold"] = m_gold;
    jOut["attack"] = m_attackSkill;
    jOut["dodge"] = m_dodgeSkill;
    jOut["toughness"] = m_toughnessSkill;
    jOut["weapon"] = m_weapon.GetName();
    jOut["inventory"] = m_itemInventory.Serialise();

    // write to file
    std::ofstream fileOut(filename);
    if (!fileOut) {
        return false;
    }
    fileOut << std::setw(2) << jOut << std::endl;
    fileOut.close();

    return true;
}

Player::Player(std::string& name)
    : Creature(name, 10), m_weapon(AvailableWeapons.at(WEAPONS::UNARMED)) {
    m_attackSkill = 50;
    m_dodgeSkill = 50;
    m_toughnessSkill = 50;
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

void Player::Reward(unsigned int gold) {
    m_gold += gold;
}

std::string Player::ToString() const {
    return Creature::ToString() + " Gold: " + std::to_string(m_gold) + "g";
}
