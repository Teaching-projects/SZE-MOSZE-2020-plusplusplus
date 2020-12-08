#include "Hero.h"
#include "JSON.h"
#include "Damage.h"

#include <fstream>
#include <vector>
#include <map>

Hero Hero::parse(const std::string &fileName)
{
    JSON properties = JSON::parseFromFile(fileName);

    const std::vector<std::string> expectedProps{"name", "base_health_points", "base_attack_cooldown", "experience_per_level", "health_point_bonus_per_level", "cooldown_multiplier_per_level", "defense", "defense_bonus_per_level", "light_radius"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (!properties.count(expectedProps[i]))
        {
            throw std::invalid_argument("File does not contain all property for Hero initialization: " + fileName + " " + expectedProps[i]);
        }
    }

    Damage dmg;

    dmg.physical = properties.getOrElse("damage", 0);
    dmg.magical = properties.getOrElse("magical_damage", 0);

    return Hero(
        properties.get<std::string>("name"),
        properties.get<int>("base_health_points"),
        dmg,
        properties.get<double>("base_attack_cooldown"),
        properties.get<int>("experience_per_level"),
        properties.get<int>("health_point_bonus_per_level"),
        properties.getOrElse<int>("damage_bonus_per_level", 0),
        properties.getOrElse<int>("magical_damage_bonus_per_level", 0),
        properties.get<double>("cooldown_multiplier_per_level"),
        properties.get<int>("defense"),
        properties.get<int>("defense_bonus_per_level"),
        properties.get<int>("light_radius"),
        properties.getOrElse<int>("light_radius_bonus_per_level", 1),
        properties.getOrElse<std::string>("texture", ""));
}

void Hero::print(std::ostream &stream) const
{
    stream << getName()
           << " - LVL" << getLevel()
           << " (HP:" << getHealthPoints() << "/" << getMaxHealthPoints()
           << ", " << getDamage()
           << ", CD:" << getAttackCoolDown()
           << ", XP:" << getXP()
           << ", DEFENSE:" << getDefense()
           << ")";
}