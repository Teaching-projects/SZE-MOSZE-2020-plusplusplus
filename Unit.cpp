#include <cmath>
#include <fstream>
#include <iostream>

#include "Unit.h"

#define LOG_TO_ERR 1

bool Unit::hit(Unit *otherUnit)
{
    // Dealing damage
    const unsigned int damageAmount = calculateDamage(otherUnit);

    // Modify healthPoints with the damage
    otherUnit->decreaseHealthPoints(damageAmount);

    // Increase XP
    this->increaseXP(damageAmount);

    this->nextAttack += this->attackCooldown;

    return !otherUnit->isAlive();
}

unsigned int Unit::calculateDamage(Unit *attackedUnit)
{
    // Base damage minus the attacked unit's defense
    const unsigned int damage = this->getDamage().sum(attackedUnit->getDefense());

    return attackedUnit->getHealthPoints() <= damage ? attackedUnit->getHealthPoints() : damage;
}

void Unit::increaseXP(unsigned int amount)
{
    unsigned int currentLevel = this->getLevel();
    this->xp += amount;
    unsigned int properLevel = this->getLevel();
    unsigned int requiredLevelUpCount = properLevel - currentLevel;

#if LOG_TO_ERR == 1
    if (requiredLevelUpCount > 0)
    {
        std::cerr << getName() << " gained " << amount
                  << " XP and leveled up " << requiredLevelUpCount << " times. (+";
    }
    unsigned int oldHp = maxHp;
    unsigned int oldDmg = damage.sum();
    double oldCD = attackCooldown;
#endif

    while (requiredLevelUpCount > 0)
    {
        this->levelUp();
        requiredLevelUpCount--;
    }

#if LOG_TO_ERR == 1
    if (oldHp != maxHp)
    {
        std::cerr << (maxHp - oldHp) << " MAX HP, +" << (damage.sum() - oldDmg) << " DMG, " << (attackCooldown - oldCD) << " CD)\n";
    }
#endif
}

void Unit::levelUp()
{
    this->maxHp += healthBonusPerLevel;
    this->hp = this->maxHp;
    this->damage.increaseDamage(damageBonusPerLevel, magicalDamageBonusPerLevel);
    this->attackCooldown = attackCooldown * cooldownMultiplier;
    this->defense += defenseBonusPerLevel;
    this->lightRadius += lightRadiusBonusPerLevel;
}

void Unit::print(std::ostream &stream) const
{
    stream << this->name
           << ": MAX HP: " << this->maxHp
           << ", HP: " << this->hp
           << ", DMG: " << this->damage
           << ", XP: " << this->xp
           << ", COOLDOWN: " << this->attackCooldown
           << ", DEFENSE: " << this->defense
           << ", LEVEL: " << this->getLevel();
}

void Unit::fightTilDeath(Unit &other)
{
    if (this == &other)
    {
        throw std::invalid_argument("The attacker Player cannot be the attacked one too");
    }

#if LOG_TO_ERR == 1
    std::cerr << std::fixed;
    std::cerr.precision(6);

    std::cerr << "\n\n----------------------------------------------------------------------------------------------------\n";

    this->print(std::cerr);
    std::cerr << " fights ";
    other.print(std::cerr);

    std::cerr << "\n------------------------------------------------------------------------------------------------------\n\n";
#endif

    this->nextAttack = this->attackCooldown;
    fight(other);
}

void Unit::fight(Unit &other)
{

#if LOG_TO_ERR == 1
    this->print(std::cerr);
    std::cerr << " attacks ";
    other.print(std::cerr);
    std::cerr << '\n';
#endif

    bool result = this->hit(&other);

#if LOG_TO_ERR == 1
    this->print(std::cerr);
    std::cerr << "         ";
    other.print(std::cerr);
    std::cerr << "\n\n";
#endif

    if (result)
    {
        return;
    }

    if (this == Unit::getNextAttacker(this, &other))
    {
        fight(other);
    }
    else
    {
        other.fight(*this);
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