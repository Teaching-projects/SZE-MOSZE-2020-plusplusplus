#pragma once

#include <string>

class Player
{
    std::string name;
    unsigned short hp;
    unsigned short damage;

public:
    explicit Player(std::string name, unsigned short hp, unsigned short damage);
    bool Attack(Player* otherPlayer);
    void Print() const;
    std::string GetName() const { return name; };
};