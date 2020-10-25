#include "Hero.h"
#include "JSON.h"

#include <fstream>
#include <regex>
#include <map>
#include <cmath>

Hero::Hero(const std::string &name, unsigned short maxhp, unsigned short damage, float attackCooldown, unsigned short xp) : name{name}, maxHp{maxhp}, hp{maxhp}, damage{damage}, attackCooldown{attackCooldown}, xp{xp}
{
}

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
        std::any_cast<float>(properties["base_attack_cooldown"]),
        0);
}

bool Hero::hit(Hero *otherPlayer)
{
    bool fatality;
    unsigned short damageAmount;

    if (otherPlayer->hp <= this->damage)
    {
        damageAmount = otherPlayer->hp;
        otherPlayer->hp = 0;
        fatality = true;
    }
    else
    {
        damageAmount = this->damage;
        otherPlayer->hp -= this->damage;
        fatality = false;
    }

    this->nextAttack += this->attackCooldown;

    // Increase XP
    this->increaseXP(damageAmount);

    return fatality;
}

void Hero::increaseXP(unsigned short amount)
{
    unsigned short currentLevel = this->getLevel();
    this->xp += amount;
    unsigned short properLevel = this->getLevel();
    unsigned short requiredLevelUpCount = properLevel - currentLevel;

    while (requiredLevelUpCount > 0)
    {
        this->levelUp();
        requiredLevelUpCount--;
    }
}

void Hero::levelUp()
{
    this->maxHp = round(this->maxHp * 1.1);
    this->hp = this->maxHp;
    this->damage = round(this->damage * 1.1);
    this->attackCooldown = this->attackCooldown * 0.9;
}

void Hero::print(std::ostream &stream) const
{
    stream << this->name
           << ": MAX HP: " << this->maxHp
           << ", HP: " << this->hp
           << ", DMG: " << this->damage
           << ", XP: " << this->xp
           << ", COOLDOWN: " << this->attackCooldown
           << ", LEVEL: " << this->getLevel();
}

void Hero::fightTilDeath(Hero &other)
{
    if (this == &other)
    {
        throw std::invalid_argument("The attacker Player cannot be the attacked one too");
    }
    if (this->hit(&other))
    {
        return;
    }
    else
    {
        if (this == Hero::getNextAttacker(this, &other))
        {
            fightTilDeath(other);
        }
        else
        {
            other.fightTilDeath(*this);
        }
    }
}

Hero *Hero::getNextAttacker(Hero *prev, Hero *other)
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