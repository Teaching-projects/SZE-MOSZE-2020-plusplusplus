#pragma once

#include <string>

#include "Unit.h"

/**
 * @class Hero 
 * 
 * @brief It defines a RPG attacker Hero.
 * 
 * It contains the main **data** what are describe the Hero and all available **actions** what the player can do or could happen with itself.
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
class Hero : public Unit
{

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
    Hero(const std::string &name, unsigned short maxHp, unsigned short damage, float attackCooldown) : Unit(name, maxHp, damage, attackCooldown){};

    /**
     * It parse a JSON object (from a JSON file) to a Hero instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param fileName Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Hero instance.
     */
    static Hero parse(const std::string &fileName);
};