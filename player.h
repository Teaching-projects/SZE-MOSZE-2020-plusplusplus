#pragma once

#include <string>

class Player
{
    std::string name;
    unsigned short hp;
    unsigned short damage;

public:
    explicit Player(const std::string &name, unsigned short hp, unsigned short damage);
    bool Attack(Player* otherPlayer) const;
    void Print() const;
    const std::string &GetName() const { return name; };
};