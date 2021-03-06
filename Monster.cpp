#include "Monster.h"
#include "JSON.h"
#include "Damage.h"

#include <fstream>
#include <vector>
#include <map>

Monster Monster::parse(const std::string &fileName)
{
    JSON properties = JSON::parseFromFile(fileName);

    const std::vector<std::string> expectedProps{"name", "health_points", "attack_cooldown", "defense"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (!properties.count(expectedProps[i]))
        {
            throw std::invalid_argument("File does not contain all property for Monster initialization: " + fileName + " " + expectedProps[i]);
        }
    }

    Damage dmg;

    dmg.physical = properties.getOrElse("damage", 0);
    dmg.magical = properties.getOrElse("magical_damage", 0);

    return Monster(
        properties.get<std::string>("name"),
        properties.get<int>("health_points"),
        dmg,
        properties.get<double>("attack_cooldown"),
        properties.get<int>("defense"),
        properties.getOrElse<std::string>("texture", ""));
}

void Monster::print(std::ostream &stream) const
{
    stream << getName()
           << " (HP:" << getHealthPoints()
           << ", " << getDamage()
           << ", CD:" << getAttackCoolDown()
           << ", DEFENSE:" << getDefense()
           << ")";
}