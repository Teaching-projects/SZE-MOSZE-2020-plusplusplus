#include "Hero.h"
#include "JSON.h"

#include <vector>
#include <map>

Hero Hero::parse(const std::string &fileName)
{
    std::map<std::string, std::any> properties = JSON::parseFromFile(fileName);

    const std::vector<std::string> expectedProps{"name", "base_health_points", "base_damage", "base_attack_cooldown"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (properties.find(expectedProps[i]) == properties.end())
        {
            throw std::invalid_argument("File does not contain all property for the Player initalization: " + fileName + " " + expectedProps[i]);
        }
    }

    return Hero(
        std::any_cast<std::string>(properties["name"]),
        std::any_cast<int>(properties["base_health_points"]),
        std::any_cast<int>(properties["base_damage"]),
        std::any_cast<float>(properties["base_attack_cooldown"]));
}