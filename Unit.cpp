#include <cmath>
#include <fstream>
#include "Unit.h"

bool Unit::hit(Unit *otherUnit)
{
    // Dealed damage
    unsigned short damageAmount = otherUnit->getHealthPoints() <= this->getDamage() ? otherUnit->getHealthPoints() : this->getDamage();

    // Modify healthPoints with the damage
    otherUnit->decreaseHealthPoints(damageAmount);

    this->nextAttack += this->attackCooldown;

    // Increase XP
    this->increaseXP(damageAmount);

    return !otherUnit->isAlive();
}

void Unit::increaseXP(unsigned short amount)
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

void Unit::levelUp()
{
    this->maxHp = round(this->maxHp * 1.1);
    this->hp = this->maxHp;
    this->damage = round(this->damage * 1.1);
    this->attackCooldown = this->attackCooldown * 0.9;
}

void Unit::print(std::ostream &stream) const
{
    stream << this->name
           << ": MAX HP: " << this->maxHp
           << ", HP: " << this->hp
           << ", DMG: " << this->damage
           << ", XP: " << this->xp
           << ", COOLDOWN: " << this->attackCooldown
           << ", LEVEL: " << this->getLevel();
}

void Unit::fightTilDeath(Unit &other)
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
        if (this == Unit::getNextAttacker(this, &other))
        {
            fightTilDeath(other);
        }
        else
        {
            other.fightTilDeath(*this);
        }
    }
}

Unit *Unit::getNextAttacker(Unit *prev, Unit *other)
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