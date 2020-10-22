#include "player.h"
#include "json.h"

#include <fstream>
#include <regex>
#include <map>
#include <cmath>

Player::Player(const std::string &name, unsigned short maxhp, unsigned short damage, float attackCooldown, unsigned short xp) : name{name}, maxHp{maxhp}, hp{maxhp}, damage{damage}, attackCooldown{attackCooldown}, xp{xp}
{
}

Player Player::parseUnit(const std::string &fileName)
{
    std::map<std::string, std::any> properties = Json::ParseFile(fileName);

    return Player(
        std::any_cast<std::string>(properties["name"]),
        std::any_cast<int>(properties["hp"]),
        std::any_cast<int>(properties["dmg"]),
        std::any_cast<float>(properties["attackcooldown"]),
        0);
}

bool Player::hit(Player *otherPlayer)
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