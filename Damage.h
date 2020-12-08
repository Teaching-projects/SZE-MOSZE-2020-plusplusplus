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

    /**
     * Add other damage to current.
     * @param damage other damage struct to be added.
     * @return current struct.
     */
    Damage &operator+=(const Damage &damage)
    {
        physical += damage.physical;
        magical += damage.magical;
        return *this;
    }

    /**
     * Multiply current struct with another.
     * @param damage other damage to multiply with.
     * @return current struct with the new values.
     */
    Damage &operator*=(const Damage &damage)
    {
        physical *= damage.physical;
        magical *= damage.magical;
        return *this;
    }

    /**
     * Add 2 structs into one.
     * @param damage left side of addition.
     * @param other right side of addition.
     * @relatesalso operator+=
     */
    friend Damage operator+(Damage damage, const Damage &other)
    {
        damage += other;
        return damage;
    }

    /**
     * Print the current damages with labels.
     * @param os output stream to write.
     * @param damage struct to write out.
     */
    friend std::ostream &operator<<(std::ostream &os, const Damage &damage)
    {
        os << "PHYSICAL DAMAGE:" << damage.physical << ", MAGICAL DAMAGE:" << damage.magical;

        return os;
    }
};