
#pragma once

#include <string>

/**
 * @class Player 
 * 
 * @brief It defines a RPG attacker Player.
 * 
 * It contains the main **data** what are describe the Player and all available **actions** what the player can do or could happen with itself.
 * 
 * The Player can duel with other players. The winner will be the player who has more damage or more health, but important paramter the attack cooldown.
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
class Player
{
    /**
     * The name of the character.
     */
    std::string name;

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
     * Count of the attacks. Zero by default.
     */
    mutable unsigned short attackCounter = 0;

public:
    /**
     * Player constructor.
     * It creates a Player object from the given parameters.
     * @param name Name of Player.
     * @param hp Health points of Player.
     * @param damage Attack damage of Player.
     * @param attackCooldown Attack cooldown of Player. **Minimum** time intervall between two attack.
     */
    explicit Player(const std::string &name, unsigned short hp, unsigned short damage, float attackCooldown);

    /**
     * It parse a JSON object (from a JSON file) to a Player instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param filename Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Player instance.
     */
    static Player parseUnit(const std::string &fileName);

    /**
     * Prints to the output the player's name and current status.
     */
    void Print() const;

    /**
     * Gets name of the player.
     * @return Player name.
     */
    const std::string &GetName() const { return name; };

    /**
     * Gets remaining health points of the player.
     * @return Player HP.
     */
    const short GetHP() const { return hp; };

    /**
     * Duel with an other player.
     * The two player going to hit each other until the first death.
     * @param other The attacked player
     * @throw std::invalid_argument When the the attacked Player equals with the attacker
     * @return The winner player of the fight
     */
    Player DuelWith(Player *other);

    /**
     * Determines from two player, who will be the next attacker.
     * It will check by the attackcooldown the time of the next attack.
     * @param prev Previous attacker player.
     * @param other Other player.
     * @return The player whose next attack's time is less than the other's.
     */
    static Player *GetNextAttacker(Player *prev, Player *other);

private:
    /**
     * The player hit an other player.
     * The attacked person's health points will less by the attacker's damage.
     * The HP cannot be less than zero.
     * @param otherPlayer The hit player.
     * @return The attacked player died in the attack or not.
     */
    bool hit(Player *otherPlayer) const;

    /**
     * It determine the time one the next attack by the attack counter.
     * @return Player's attack cooldown multipled by the attack count.
     */
    float getNextAttack() const;
};