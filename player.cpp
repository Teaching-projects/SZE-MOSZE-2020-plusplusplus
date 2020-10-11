#include "player.h"

#include <fstream>
#include <regex>

Player::Player(const std::string &name, unsigned short hp, unsigned short damage, float attackCooldown) : name{name}, hp{hp}, damage{damage}, attackCooldown{attackCooldown}
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

    static const std::regex jsonParseRegex("\\s*\"([a-z]*)\"\\s*:\\s*\"?(\\w*.?\\w+)\"?\\s*[,}]\\s*");
    std::map<std::string, std::string> properties;
    while (std::regex_search(jsonString, matches, jsonParseRegex))
    {
        if (matches.size() == 3)
        {
            properties[matches[1]] = matches[2];
        }
        jsonString = matches.suffix();
    }

    const std::vector<std::string> expectedProps{"name", "hp", "dmg", "attackcooldown"};
    for (unsigned int i = 0; i < expectedProps.size(); i++)
    {
        if (properties.find(expectedProps[i]) == properties.end())
        {
            throw std::invalid_argument("File does not contain all property for the Player initalization: " + fileName + " " + expectedProps[i]);
        }
    }

    return Player(properties["name"], stoi(properties["hp"]), stoi(properties["dmg"]), stof(properties["attackcooldown"]));
}

bool Player::hit(Player *otherPlayer) const
{
    if (otherPlayer->hp <= this->damage)
    {
        otherPlayer->hp = 0;
        return true;
    }

    otherPlayer->hp -= this->damage;
    this->attackCounter++;
    return false;
}

void Player::Print(std::ostream &stream) const
{
    stream << this->name << ": HP: " << this->hp << ", DMG: " << this->damage << '\n';
}

Player Player::DuelWith(Player *other)
{
    if (this == other)
    {
        throw std::invalid_argument("The attacker Player cannot be the attacked one too");
    }
    if (this->hit(other))
    {
        return *this;
    }
    else
    {
        if (this == Player::GetNextAttacker(this, other))
        {
            return this->DuelWith(other);
        }
        else
        {
            return other->DuelWith(this);
        }
    }
}

float Player::getNextAttack() const
{
    return this->attackCooldown * this->attackCounter;
}

Player *Player::GetNextAttacker(Player *prev, Player *other)
{
    if (prev->getNextAttack() <= other->getNextAttack())
    {
        return prev;
    }
    else
    {
        return other;
    }
}