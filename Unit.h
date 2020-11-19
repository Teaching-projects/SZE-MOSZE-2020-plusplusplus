#pragma once

#include <string>

// By default these are set to 0 to "disable" the feature
#define LEVEL_SIZE 0
#define HEALTH_BONUS 0
#define DAMAGE_BONUS 0
#define DEFENSE_BONUS 0
#define COOLDOWN_MULTIPLIER 1 // 1 to avoid changing value

/**
 * @class Unit 
 * 
 * @brief It defines a RPG attacker Unit.
 * 
 * It contains the main properties and **actions** what the unit can do or could happen with it.
 * 
 * The Unit can duel with other units. The winner will be the unit which has more damage or more health, but the attack cooldown parameter can twist the result.
 * The lower cooldown makes the Unit faster than the other.
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
    unsigned int maxHp;

    /**
     * The health point of the character.
     */
    unsigned int hp;

    /**
     * The damage of the character.
     */
    unsigned int damage;

    /**
     * The attack cooldown of the character.
     */
    double attackCooldown;

    /**
     * The time of the next attack (**in seconds**).
     * Zero by default.
     */
    double nextAttack = 0;

    /**
     * The xp of the character.
     */
    unsigned int xp = 0;

    /**
     * The experince per level.
     * Defauls to the define directive
     */
    unsigned int xpPerLevel = LEVEL_SIZE;

    /**
     *  The extra healthpoints added per levelups.
     *  Defaults to define directive
     */
    unsigned int healthBonusPerLevel = HEALTH_BONUS;

    /**
     *  The extra damage added per levelups.
     *  Defaults to define directive
     */
    unsigned int damageBonusPerLevel = DAMAGE_BONUS;

    /**
     *  The multiplier of cooldown decrease, per levelup.
     *  Defaults to define directive
     */
    double cooldownMultiplier = COOLDOWN_MULTIPLIER;

    /**
     * Defense abality size.
     * How many damage can the player defend.
     */
    unsigned int defense;

    /**
     * The defense added per levelups.
     * Defaults to define directive.
     */
    unsigned int defenseBonusPerLevel = DEFENSE_BONUS;

protected:
    /**
     * The unit hit an other unit.
     * The attacked Unit's health points will less by the attacker's damage.
     * *The HP cannot be less than zero*.
     * @param otherPlayer The hit unit.
     * @return The attacked unit died in the attack or not.
     */
    bool hit(Unit *otherUnit);

    /**
     * It returns with the next attack's time (**in seconds**). 
     * @return next attack identifier.
     */
    double getNextAttack() const { return nextAttack; };

    /**
     * Increase the unit's XP by the given amount.
     * @param amount Addation XP score.
     */
    void increaseXP(unsigned int amount);

    /**
     * Modify the unit settings for the next level.
     * Increase maximum HP and damage by **10%**.
     * **Refill** the current HP to the new maximum.
     * Decrease CD by **10%**.
     */
    void levelUp();

    /**
     * Decrease current health according to parameter.
     */
    void decreaseHealthPoints(unsigned int damage)
    {
        this->hp -= damage;
    };

    /**
     * Handle a single fight round. Units will call on each other until
     * one of the produces a lethal hit
     */
    void fight(Unit &other);

    /**
     * Calculate delead damage to the given other Unit.
     * Dealed damage cannot be bigger than the other unit's HP.
     * Dealed damage is defendable by defense points.
     * Dealed damage is cannot be less than 0.
     * @param attackedUnit The attacked unit.
     * @return Damage.
     */
    unsigned int calculateDamage(Unit *attackedUnit);

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
    Unit(const std::string &name, unsigned int maxHp, unsigned int damage, double attackCooldown, unsigned int defense) : name(name), maxHp(maxHp), hp(maxHp), damage(damage), attackCooldown(attackCooldown), nextAttack(attackCooldown), defense(defense){};

    /**
     * Unit constructor.
     * It creates a Unit object from the given parameters.
     * @param name Name of Unit.
     * @param hp Health points of Unit.
     * @param damage Attack damage of Unit.
     * @param attackCooldown Attack cooldown of Unit. **Minimum** time intervall between two attack.
     * @param xpPerLevel XP needed for a levelup
     * @param healthBonusPerLevel The extra healthpoints added per levelups.
     * @param damageBonusPerLevel The extra damage added per levelups.
     * @param cooldownMultiplier Multiplier for cooldown on levelup
     */
    Unit(const std::string &name, unsigned int maxHp, unsigned int damage, double attackCooldown, unsigned int xpPerLevel, unsigned int healthBonusPerLevel, unsigned int damageBonusPerLevel, double cooldownMultiplier, unsigned int defense, unsigned int defenseBonusPerLevel) : name(name), maxHp(maxHp), hp(maxHp), damage(damage), attackCooldown(attackCooldown), nextAttack(attackCooldown), xpPerLevel(xpPerLevel), healthBonusPerLevel(healthBonusPerLevel), damageBonusPerLevel(damageBonusPerLevel), cooldownMultiplier(cooldownMultiplier), defense(defense), defenseBonusPerLevel(defenseBonusPerLevel){};

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
    virtual void print(std::ostream &stream) const;

    /**
     * Gets name of the unit.
     * @return Unit name. 
     */
    const std::string &getName() const { return name; };

    /**
     * Get Unit's damage points.
     * @return Current damage size.
     */
    unsigned int getDamage() const { return this->damage; };

    /**
     * Gets maximum health points of the unit.
     * @return Unit Max HP.
     */
    unsigned int getMaxHealthPoints() const { return maxHp; };

    /**
     * Gets remaining health points of the unit.
     * @return Unit HP.
     */
    unsigned int getHealthPoints() const { return hp; };

    /**
     * Gets the cooldown of the unit.
     * @return Unit Attack Cooldown.
     */
    double getAttackCoolDown() const { return attackCooldown; };

    /**
     * Gets xp of the unit.
     * @return Unit XP.
     */
    unsigned int getXP() const { return xp; };

    /**
     * Duel with an other unit.
     * The two unit going to hit each other until the first death.
     * @param other The attacked unit.
     * @throw std::invalid_argument When the the attacked Unit equals with the attacker.
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
     * @return Current level.
     */
    unsigned int getLevel() const { return xpPerLevel == 0 ? 1 : ((xp / xpPerLevel) + 1); };

    /**
     * The unit is alive or dead.
     * It determines from the health points. If it equals with 0, the unit is dead.
     * @return Is alive status.
     */
    bool isAlive() const
    {
        return this->getHealthPoints() != 0;
    };

    /**
     * Gets the unit's defense points.
     * @return Amount of defense.
     */
    unsigned int getDefense() const { return this->defense; };
};