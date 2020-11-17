#pragma once

#include "Unit.h"

/**
 * @class Monster 
 * 
 * @brief It defines a RPG Monster, enemy of Hero.
 * 
 * It contains the main **data** what are describe the Monster and all available **actions** what the player can do or could happen with itself.
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
class Monster : public Unit
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
    explicit Monster(const std::string &name, unsigned short maxHp, unsigned short damage, double attackCooldown, unsigned short defense, unsigned short defenseBonusPerLevel) : Unit(name, maxHp, damage, attackCooldown, defense, defenseBonusPerLevel){};

    /**
     * It parse a JSON object (from a JSON file) to a Monster instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param filename Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Monster instance.
     */
    static Monster parse(const std::string &fileName);

    /**
     * Override the parent class method, print custom format.
     */
    void print(std::ostream &stream) const;
};