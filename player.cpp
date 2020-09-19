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

    const std::regex regex("\\s*\"([a-z]*)\"\\s*:\\s*\"?([A-Za-z0-9]*)\"?[,}]\\s*");
    std::smatch matches;

    std::map<std::string, std::string> properties;
    while (std::regex_search(jsonString, matches, regex))
    {
        if (matches.size() == 3)
        {
            properties[matches[1]] = matches[2];
        }
        jsonString = matches.suffix();
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
