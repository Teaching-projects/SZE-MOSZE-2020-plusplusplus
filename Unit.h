#pragma once

#include <string>

#define LEVEL_SIZE 100

/**
 * @class Unit 
 * 
 * @brief It defines a RPG attacker Unit.
 * 
 * It contains the main **data** what are describe the Hero and all available **actions** what the unit can do or could happen with itself.
 * 
 * The Hero can duel with other heroes. The winner will be the unit who has more damage or more health, but important paramter the attack cooldown.
 * With smaller cooldown the unit hit the other unit faster.
 * 
 * @note It contains recursive solutions
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-10-28
 * 
 * Created on: 2020-10-28
 * 
*/

class Unit
{
private:
    /**
     * The name of the character.
     */
    const std::string name;

    /**
     * The maximum health point of the character.
     */
    unsigned short maxHp;

    /**
     * The health point of the character.
     */
    unsigned short hp;

    /**
     * The damage of the character.
     */
    unsigned short damage;

    /**
     * The attack cooldown of the character.
     */
    float attackCooldown;

    /**
     * The time of the next attack (**in seconds**).
     * Zero by default.
     */
    float nextAttack = 0;

    /**
     * The xp of the character.
     */
    unsigned short xp = 0;

protected:
    /**
     * The unit hit an other unit.
     * The attacked person's health points will less by the attacker's damage.
     * *The HP cannot be less than zero*.
     * @param otherPlayer The hit unit.
     * @return The attacked unit died in the attack or not.
     */
    bool hit(Unit *otherUnit);

    /**
     * It returns with the next attack's time (**in seconds**). 
     * @return next attack identifier.
     */
    float getNextAttack() const { return nextAttack; };

    /**
     * Increase the unit's XP by the given amount.
     * @param amount Addation XP score.
     */
    void increaseXP(unsigned short amount);

    /**
     * Modify the unit settings for the next level.
     * Increase maximum HP and damage by **10%**.
     * **Refill** the current HP to the new maximum.
     * Decrease CD by **10%**.
     */
    void levelUp();

    /**
     * Get Unit's damage points.
     * @return Current damage size.
     */
    unsigned short getDamage() const { return this->damage; };

    void decreaseHealthPoints(unsigned short damage)
    {
        this->hp -= damage;
    };

public:
    /**
     * Unit constructor.
     * It creates a Unit object from the given parameters.
     * @param name Name of Unit.
     * @param hp Health points of Unit.
     * @param damage Attack damage of Unit.
     * @param attackCooldown Attack cooldown of Unit. **Minimum** time intervall between two attack.
     * @param xp Starter experience point of the character.
     */
    Unit(const std::string &name, unsigned short maxHp, unsigned short damage, float attackCooldown) : name(name), maxHp(maxHp), hp(maxHp), damage(damage), attackCooldown(attackCooldown){};

    /**
     * It parse a JSON object (from a JSON file) to a Unit instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param filename Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Unit instance.
     */
    static Unit parse(const std::string &fileName);

    /**
     * Prints to the output the unit's name and current status.
     * @param stream The destination output stream
     */
    void print(std::ostream &stream) const;

    /**
     * Gets name of the unit.
     * @return Hero name. 
     */
    const std::string &getName() const { return name; };

    /**
     * Gets maximum health points of the unit.
     * @return Hero Max HP.
     */
    unsigned short getMaxHP() const { return maxHp; };

    /**
     * Gets remaining health points of the unit.
     * @return Hero HP.
     */
    unsigned short getHealthPoints() const { return hp; };

    /**
     * Gets xp of the unit.
     * @return Hero XP.
     */
    unsigned short getXP() const { return xp; };

    /**
     * Duel with an other unit.
     * The two unit going to hit each other until the first death.
     * @param other The attacked unit.
     * @throw std::invalid_argument When the the attacked Unit equals with the attacker.
     * @return The winner unit of the fight.
     */
    void fightTilDeath(Unit &other);

    /**
     * Determines from two unit, who will be the next attacker.
     * It will check by the attackcooldown the time of the next attack.
     * @param prev Previous attacker unit.
     * @param other Other unit.
     * @return The unit whose next attack's time is less than the other's.
     */
    static Unit *getNextAttacker(Unit *prev, Unit *other);

    /**
     * Gets the unit's current level determined from the character's XP score.
     */
    unsigned short getLevel() const { return (xp / LEVEL_SIZE) + 1; };

    /**
     * The unit is alive or dead.
     * It determines from the health points. If it equals with 0, the unit is dead.
     * @return Is alive status.
     */
    bool isAlive() const
    {
        return this->getHealthPoints() != 0;
    };
};