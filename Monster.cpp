#include "Monster.h"
#include "JSON.h"

#include <vector>
#include <map>

Monster Monster::parse(const std::string &fileName)
{
    std::map<std::string, std::any> properties = JSON::parseFromFile(fileName);

    const std::vector<std::string> expectedProps{"name", "health_points", "damage", "attack_cooldown"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (properties.find(expectedProps[i]) == properties.end())
        {
            throw std::invalid_argument("File does not contain all property for the Monster initalization: " + fileName + " " + expectedProps[i]);
        }
    }

    return Monster(
        std::any_cast<std::string>(properties["name"]),
        std::any_cast<int>(properties["health_points"]),
        std::any_cast<int>(properties["damage"]),
        std::any_cast<float>(properties["attack_cooldown"]));
}