#include "player.h"

#include <iostream>

Player::Player(std::string name, unsigned short hp, unsigned short damage)
{
    this->name = name;
    this->hp = hp;
    this->damage = damage;
}

bool Player::Attack(Player* otherPlayer)
{
    if (otherPlayer->hp <= this->damage)
    {
        otherPlayer->hp = 0;
        return true;
    }

    otherPlayer->hp -= this->damage;
    return false;
}

void Player::Print() const
{
    std::cout << this->name << ": HP: " << this->hp << ", DMG: " << this->damage << '\n';
}