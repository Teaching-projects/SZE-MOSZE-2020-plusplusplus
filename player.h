#pragma once

#include <string>

class Player
{
    std::string name;
    unsigned short hp;
    unsigned short damage;

public:
    void Read(char **argv, int nthPlayer);
    bool Attack(Player *otherPlayer);
    void Print();
    std::string GetName() const { return name; };
};