#pragma once

#include "Hero.h"

/**
 * @class Monster 
 * 
 * @brief It defines a RPG Monster, enemy of Hero.
 * 
 * It contains the main **data** what are describe the Monster and all available **actions** what the player can do or could happen with itself.
 * 
 * The Monster can duel with other heroes. The winner will be the player who has more damage or more health, but important paramter the attack cooldown.
 * With smaller cooldown the player hit the other player faster.
 * 
 * @note It contains recursive solutions
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-10-25
 * 
 * Created on: 2020-10-25
 * 
*/
class Monster : public Hero
{
public:
    /**
     * Monster constructor.
     * It creates a Monster object from the given parameters.
     * @param name Name of Monster.
     * @param hp Health points of Monster.
     * @param damage Attack damage of Monster.
     * @param attackCooldown Attack cooldown of Monster. **Minimum** time intervall between two attack.
     * @param xp Starter experience point of the character.
     */
    explicit Monster(const std::string &name, unsigned short maxhp, unsigned short damage, float attackCooldown, unsigned short xp);

    /**
     * It parse a JSON object (from a JSON file) to a Monster instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param filename Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Monster instance.
     */
    static Monster parse(const std::string &fileName);
};