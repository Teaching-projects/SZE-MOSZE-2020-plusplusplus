#pragma once

#include <string>
#include <iostream>
#define LEVEL_SIZE 100

/**
 * @class Hero 
 * 
 * @brief It defines a RPG attacker Hero.
 * 
 * It contains the main **data** what are describe the Hero and all available **actions** what the player can do or could happen with itself.
 * 
 * The Hero can duel with other heroes. The winner will be the player who has more damage or more health, but important paramter the attack cooldown.
 * With smaller cooldown the player hit the other player faster.
 * 
 * @note It contains recursive solutions
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-10-07
 * 
 * Created on: 2020-10-07
 * 
*/
class Hero
{
protected:
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
    unsigned short xp;

public:
    /**
     * Hero constructor.
     * It creates a Hero object from the given parameters.
     * @param name Name of Hero.
     * @param hp Health points of Hero.
     * @param damage Attack damage of Hero.
     * @param attackCooldown Attack cooldown of Hero. **Minimum** time intervall between two attack.
     * @param xp Starter experience point of the character.
     */
    explicit Hero(const std::string &name, unsigned short maxhp, unsigned short damage, float attackCooldown, unsigned short xp);

    /**
     * It parse a JSON object (from a JSON file) to a Hero instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param fileName Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Hero instance.
     */
    static Hero parse(const std::string &fileName);

    /**
     * Prints to the output the player's name and current status.
     * @param stream The destination output stream
     */
    void print(std::ostream &stream) const;

    /**
     * Gets name of the player.
     * @return Hero name.
     */
    const std::string &getName() const { return name; };

    /**
     * Gets maximum health points of the player.
     * @return Hero Max HP.
     */
    short getMaxHP() const { return maxHp; };

    /**
     * Gets remaining health points of the player.
     * @return Hero HP.
     */
    short getHealthPoints() const { return hp; };

    /**
     * Gets xp of the player.
     * @return Hero XP.
     */
    short getXP() const { return xp; };

    /**
     * Duel with an other player.
     * The two player going to hit each other until the first death.
     * @param other The attacked player.
     * @throw std::invalid_argument When the the attacked Hero equals with the attacker.
     * @return The winner player of the fight.
     */
    void fightTilDeath(Hero other);

    /**
     * Determines from two player, who will be the next attacker.
     * It will check by the attackcooldown the time of the next attack.
     * @param prev Previous attacker player.
     * @param other Other player.
     * @return The player whose next attack's time is less than the other's.
     */
    static Hero *getNextAttacker(Hero *prev, Hero *other);

    /**
     * Gets the character's current level determined from the character's XP score.
     */
    short getLevel() const { return (xp / LEVEL_SIZE) + 1; };

    bool isAlive() const
    {
        return this->getHealthPoints() != 0;
    }

private:
    /**
     * The player hit an other player.
     * The attacked person's health points will less by the attacker's damage.
     * *The HP cannot be less than zero*.
     * @param otherPlayer The player who has been hit.
     * @return The attacked player died in the attack or not.
     */
    bool hit(Hero *otherPlayer);

    /**
     * It returns with the next attack's time (**in seconds**). 
     * @return Next attack time.
     */
    float getNextAttack() const { return nextAttack; };

    /**
     * Increase the character's XP by the given amount.
     * @param amount Addation XP score.
     */
    void increaseXP(unsigned short amount);

    /**
     * Modify the character settings for the next level.
     * Increase maximum HP and damage by **10%**.
     * **Refill** the current HP to the new maximum.
     * Decrease CD by **10%**.
     */
    void levelUp();
};