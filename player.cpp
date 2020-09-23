#include "player.h"

#include <iostream>
#include <fstream>
#include <regex>

Player::Player(const std::string &name, unsigned short hp, unsigned short damage) : name{name}, hp{hp}, damage{damage}
{
}

Player Player::parseUnit(const std::string &fileName)
{
    std::ifstream jsonFile(fileName);

    if (jsonFile.fail())
    {
        const std::string errMessage("Error: No such file: " + fileName);
        throw std::runtime_error(errMessage);
    }

    std::string jsonString;
    std::string lineString;
    while (getline(jsonFile, lineString))
    {
        jsonString += lineString;
    }

    jsonFile.close();

    std::smatch matches;

    static const std::regex jsonParseRegex("\\s*\"([a-z]*)\"\\s*:\\s*\"?([\\w]*)\"?\\s*[,}]\\s*");
    std::map<std::string, std::string> properties;
    while (std::regex_search(jsonString, matches, jsonParseRegex))
    {
        if (matches.size() == 3)
        {
            properties[matches[1]] = matches[2];
        }
        jsonString = matches.suffix();
    }

    const std::vector<std::string> props{"name", "hp", "dmg"};
    for (int i = 0; i < props.size(); i++)
    {
        if (properties.find(props[i]) == properties.end())
        {
            throw std::invalid_argument("File does not contain all property for the Player initalization: " + fileName);
        }
    }

    return Player(properties["name"], stoi(properties["hp"]), stoi(properties["dmg"]));
}

bool Player::Attack(Player *otherPlayer) const
{
    if (otherPlayer->hp <= this->damage)
    {
        otherPlayer->hp = 0;
        return true;
    }

    otherPlayer->hp -= this->damage;
    return false;
}

void Player::Print() const
{
    std::cout << this->name << ": HP: " << this->hp << ", DMG: " << this->damage << '\n';
}