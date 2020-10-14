#include "player.h"

#include <fstream>
#include <regex>
#include <map>
#include <math.h>

Player::Player(const std::string &name, unsigned short maxhp, unsigned short damage, float attackCooldown, unsigned short xp) : name{name}, maxHp{maxhp}, hp{maxhp}, damage{damage}, attackCooldown{attackCooldown}, xp{xp}
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

    return Player(properties["name"], stoi(properties["hp"]), stoi(properties["dmg"]), stof(properties["attackcooldown"]), 0);
}

bool Player::hit(Player *otherPlayer)
{
    bool fatality;

    if (otherPlayer->hp <= this->damage)
    {
        otherPlayer->hp = 0;
        fatality = true;
    }
    else
    {
        otherPlayer->hp -= this->damage;
        fatality = false;
    }

    this->nextAttack += this->attackCooldown;
    // Increase XP
    this->increaseXP(this->damage);

    return fatality;
}

void Player::increaseXP(unsigned short amount)
{
    unsigned short currentLevel = this->GetLevel();
    this->xp += amount;
    unsigned short properLevel = this->GetLevel();
    unsigned short requiredLevelUpCount = properLevel - currentLevel;

    while (requiredLevelUpCount > 0)
    {
        this->levelUp();
        requiredLevelUpCount--;
    }
}

void Player::levelUp()
{
    this->maxHp = round(this->maxHp * 1.1);
    this->hp = this->maxHp;
    this->damage = round(this->damage * 1.1);
    this->attackCooldown = this->attackCooldown * 0.9;
}

void Player::Print(std::ostream &stream) const
{
    stream << this->name
           << ": MAX HP: " << this->maxHp
           << ", HP: " << this->hp
           << ", DMG: " << this->damage
           << ", XP: " << this->xp
           << ", COOLDOWN: " << this->attackCooldown
           << ", LEVEL: " << this->GetLevel();
}

Player *Player::DuelWith(Player *other)
{
    if (this == other)
    {
        throw std::invalid_argument("The attacker Player cannot be the attacked one too");
    }
    if (this->hit(other))
    {
        return this;
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