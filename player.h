#pragma once

#include <string>

class Player
{
    std::string name;
    unsigned short hp;
    unsigned short damage;
    float attackCooldown;
    mutable unsigned short attackCounter = 0;

public:
    explicit Player(const std::string &name, unsigned short hp, unsigned short damage, float attackCooldown);
    static Player parseUnit(const std::string &fileName);
    bool Attack(Player *otherPlayer) const;
    void Print() const;
    const std::string &GetName() const { return name; };
    const short GetHP() const { return hp; };
    float GetNextAttack() const;
};