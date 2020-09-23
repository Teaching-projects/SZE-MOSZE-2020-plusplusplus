#pragma once

#include <string>
#include <regex>

class Player
{
    std::string name;
    unsigned short hp;
    unsigned short damage;
    static std::regex jsonParseRegex;

public:
    explicit Player(const std::string &name, unsigned short hp, unsigned short damage);
    static Player parseUnit(const std::string &fileName);
    bool Attack(Player *otherPlayer) const;
    void Print() const;
    const std::string &GetName() const { return name; };
    const short GetHP() const { return hp; };
};