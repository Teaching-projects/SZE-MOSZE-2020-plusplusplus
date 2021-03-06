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
     * @param maxHp Health points of Hero.
     * @param damage Attack damage of Hero.
     * @param attackCooldown Attack cooldown of Hero. **Minimum** time intervall between two attack.
     * @param xpPerLevel XP needed for a levelup
     * @param healthBonusPerLevel The extra healthpoints added per levelups.
     * @param damageBonusPerLevel The extra damage added per levelups.
     * @param magicalDamageBonusPerLevel The extra magical damage added per levelups.
     * @param cooldownMultiplier Multiplier for cooldown on levelup.
     * @param defense Defense of the Hero.
     * @param defenseBonusPerLevel The extra defense added per levelups.
     * @param lightRadius Light radius of Hero.
     * @param lightRadiusBonusPerLevel Addational range on every levels.
     * @param texture Texture image file
    */
    Hero(const std::string &name, unsigned int maxHp, Damage damage, double attackCooldown, unsigned int xpPerLevel, unsigned int healthBonusPerLevel, unsigned int damageBonusPerLevel, unsigned int magicalDamageBonusPerLevel, double cooldownMultiplier, unsigned int defense, unsigned int defenseBonusPerLevel, unsigned int lightRadius, unsigned int lightRadiusBonusPerLevel, const std::string &texture) : Unit(name, maxHp, damage, attackCooldown, xpPerLevel, healthBonusPerLevel, damageBonusPerLevel, magicalDamageBonusPerLevel, cooldownMultiplier, defense, defenseBonusPerLevel, lightRadius, lightRadiusBonusPerLevel, texture){};

    /**
     * It parse a JSON object (from a JSON file) to a Hero instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param fileName Json file's path.
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