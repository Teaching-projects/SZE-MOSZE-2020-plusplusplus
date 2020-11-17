#pragma once

#include <string>
#include "Damage.h"
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
     * @param xpPerLevel XP needed for a levelup
     * @param healthBonusPerLevel The extra healthpoints added per levelups.
     * @param damageBonusPerLevel The extra damage added per levelups.
     * @param cooldownMultiplier Multiplier for cooldown on levelup.
     * @param damage Defense of the Hero.
     * @param damageBonusPerLevel The extra defense added per levelups.
    */
    Hero(const std::string &name, unsigned short maxHp, Damage damage, double attackCooldown, unsigned short xpPerLevel, unsigned short healthBonusPerLevel, unsigned short damageBonusPerLevel, double cooldownMultiplier, unsigned short defense, unsigned short defenseBonusPerLevel) : Unit(name, maxHp, damage, attackCooldown, xpPerLevel, healthBonusPerLevel, damageBonusPerLevel, cooldownMultiplier, defense, defenseBonusPerLevel){};

    /**
     * It parse a JSON object (from a JSON file) to a Hero instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param filename Json file's path.
     * @throw JSON::ParseException When the file does not openable or the file format is invalid
     * @throw out_of_range is thrown if the number to be parsed too large
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Hero instance.
     */
    static Hero parse(const std::string &fileName);

    /**
     * Override the parent class method, print custom format.
     * @param stream Output stream for print.
     */
    void print(std::ostream &stream) const override;
};