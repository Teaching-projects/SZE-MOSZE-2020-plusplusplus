#include "player.h"

#include <iostream>
#include <fstream>

Player::Player(const std::string &name, unsigned short hp, unsigned short damage) : name{name}, hp{hp}, damage{damage}
{
}

std::regex Player::jsonParseRegex("\\s*\"([a-z]*)\"\\s*:\\s*\"?([\\w]*)\"?\\s*[,}]\\s*");

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

    std::map<std::string, std::string> properties;
    while (std::regex_search(jsonString, matches, Player::jsonParseRegex))
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
