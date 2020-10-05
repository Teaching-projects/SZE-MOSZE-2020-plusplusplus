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
    void Print() const;
    const std::string &GetName() const { return name; };
    const short GetHP() const { return hp; };
    Player DuelWith(Player *other);
    static Player *GetNextAttacker(Player *prev, Player *other);

private:
    bool attack(Player *otherPlayer) const;
    float getNextAttack() const;
};