#pragma once

#include "Hero.h"

class Monster : public Hero
{
public:
    /**
     * Player constructor.
     * It creates a Player object from the given parameters.
     * @param name Name of Player.
     * @param hp Health points of Player.
     * @param damage Attack damage of Player.
     * @param attackCooldown Attack cooldown of Player. **Minimum** time intervall between two attack.
     * @param xp Starter experience point of the character.
     */
    explicit Monster(const std::string &name, unsigned short maxhp, unsigned short damage, float attackCooldown, unsigned short xp);

    /**
     * It parse a JSON object (from a JSON file) to a Player instance.
     * Does not matter the order of the object properties, but it have to contain all required propertiy.
     * @param filename Json file's path.
     * @throw std::runtime_error When the file does not openable.
     * @throw std::invalid_argument When the file does not contain a required field
     * @return Created Player instance.
     */
    static Monster parse(const std::string &fileName);
};