#pragma once

#include <iostream>

struct Damage
{
    unsigned int physical = 0;
    unsigned int magical = 0;

    int sum()
    {
        return physical + magical;
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