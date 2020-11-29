#pragma once

#include <iostream>

/**
 * Damage struct
 */
struct Damage
{
    /**
     * Physical damage.
     */
    unsigned int physical = 0;

    /**
     * Magical damage.
    */
    unsigned int magical = 0;

    /**
     * Summary damage.
     * @return Physical plus magical damage.
     */
    unsigned int sum()
    {
        return physical + magical;
    }

    /**
     * Summary damage minus the the given defense points.
     * @param defense Defense points against the physical damage.
     * @return Phyiscal plus magical damage minus defense amount.
     */
    unsigned int sum(unsigned int defense)
    {
        return (physical <= defense ? 0 : physical - defense) + magical;
    }

    /**
     * Increase damage.
     * @param phy Physical damage increase.
     * @param mag Magical damage increase.
     */
    void increaseDamage(unsigned int phy, unsigned int mag)
    {
        physical += phy;
        magical += mag;
    }

    Damage &operator+=(const Damage &damage)
    {
        physical += damage.physical;
        magical += damage.magical;
        return *this;
    }

    Damage &operator*=(const Damage &damage)
    {
        physical *= damage.physical;
        magical *= damage.magical;
        return *this;
    }

    friend Damage operator+(Damage damage, const Damage &other)
    {
        damage += other;
        return damage;
    }

    friend std::ostream &operator<<(std::ostream &os, const Damage &damage)
    {
        os << "PHYSICAL DAMAGE:" << damage.physical << ", MAGICAL DAMAGE:" << damage.magical;

        return os;
    }
};