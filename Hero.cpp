#include "Hero.h"
#include "JSON.h"

#include <fstream>
#include <vector>
#include <map>

Hero Hero::parse(const std::string &fileName)
{
    JSON properties = JSON::parseFromFile(fileName);

    const std::vector<std::string> expectedProps{"name", "base_health_points", "base_damage", "base_attack_cooldown"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (!properties.count(expectedProps[i]))
        {
            throw std::invalid_argument("File does not contain all property for the Player initalization: " + fileName + " " + expectedProps[i]);
        }
    }

    return Hero(
        properties.get<std::string>("name"),
        properties.get<int>("base_health_points"),
        properties.get<int>("base_damage"),
        properties.get<float>("base_attack_cooldown"),
        properties.get<int>("experience_per_level"),
        properties.get<int>("health_point_bonus_per_level"),
        properties.get<int>("damage_bonus_per_level"),
        properties.get<float>("cooldown_multiplier_per_level"));
}

void Hero::print(std::ostream &stream) const
{
    stream << getName()
           << " - LVL" << getLevel()
           << " (HP:" << getHealthPoints() << "/" << getMaxHealthPoints()
           << ", DMG:" << getDamage()
           << ", CD:" << getAttackCoolDown()
           << ", XP:" << getXP() << ")";
}