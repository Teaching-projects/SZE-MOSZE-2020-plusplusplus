#include "player.h"

#include <iostream>
#include <fstream>
#include <regex>

Player::Player(const std::string &name, unsigned short hp, unsigned short damage) : name{name}, hp{hp}, damage{damage}
{
}

Player Player::parseUnit(const std::string &fileName)
{
    std::string lineString;
    std::string jsonString;

    std::ifstream jsonFile(fileName);

    if (jsonFile.fail())
    {
        const std::string errMessage("Error: No such file: " + fileName);
        throw std::runtime_error(errMessage);
    }

    while (getline(jsonFile, lineString))
    {
        jsonString += lineString;
    }

    jsonFile.close();

    const std::string spaceRegex("^ +| +$|( ) +");
    const std::string specialCharacterRegex("[{}\"]");

    jsonString = std::regex_replace(jsonString, std::regex(spaceRegex), "");
    jsonString = std::regex_replace(jsonString, std::regex(specialCharacterRegex), "");
    jsonString = std::regex_replace(jsonString, std::regex(","), ":");

    std::vector<std::string> properties;
    std::string aValue{""};

    // Split
    for (char character : jsonString)
    {
        if (character != ':')
            aValue += character;
        else if (character == ':' && aValue != "")
        {
            properties.push_back(std::regex_replace(aValue, std::regex(spaceRegex), ""));
            aValue = "";
        }
    }

    if (aValue != "")
        properties.push_back(std::regex_replace(aValue, std::regex(spaceRegex), ""));

    return Player(properties[1], stoi(properties[3]), stoi(properties[5]));
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
