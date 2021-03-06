#pragma once

#include "Unit.h"
#include "Damage.h"

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
     * @param maxHp Health points of Monster.
     * @param damage Attack damage of Monster.
     * @param attackCooldown Attack cooldown of Monster. **Minimum** time intervall between two attack.
     * @param defense Defense of the Monster.
     * @param texture Texture image file
     */
    explicit Monster(const std::string &name, unsigned int maxHp, Damage damage, double attackCooldown, unsigned int defense, const std::string &texture) : Unit(name, maxHp, damage, attackCooldown, defense, texture){};

    /**
     * It parse a JSON object (from a JSON file) to a Monster instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param fileName Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Monster instance.
     */
    static Monster parse(const std::string &fileName);

    /**
     * Override the parent class method, print custom format.
     * @param stream Output stream for print.
     */
    void print(std::ostream &stream) const override;
};