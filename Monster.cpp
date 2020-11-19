#include "Monster.h"
#include "JSON.h"

#include <fstream>
#include <vector>
#include <map>

Monster Monster::parse(const std::string &fileName)
{
    JSON properties = JSON::parseFromFile(fileName);

    const std::vector<std::string> expectedProps{"name", "health_points", "damage", "attack_cooldown", "defense"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (!properties.count(expectedProps[i]))
        {
            throw std::invalid_argument("File does not contain all property for the Monster initalization: " + fileName + " " + expectedProps[i]);
        }
    }

    return Monster(
        properties.get<std::string>("name"),
        properties.get<int>("health_points"),
        properties.get<int>("damage"),
        properties.get<double>("attack_cooldown"),
        properties.get<int>("defense"));
}

void Monster::print(std::ostream &stream) const
{
    stream << getName()
           << " (HP:" << getHealthPoints()
           << ", DMG:" << getDamage()
           << ", CD:" << getAttackCoolDown()
           << ", DEFENSE:" << getDefense()
           << ")";
}