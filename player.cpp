#include "player.h"

#include <iostream>

void Player::Read(char **argv, int nthPlayer)
{
    int start = 1 + (nthPlayer * 3);
    this->name = argv[start];
    this->hp = atoi(argv[start + 1]);
    this->damage = atoi(argv[start + 2]);
}

bool Player::Attack(Player *otherPlayer)
{
    if (otherPlayer->hp <= this->damage)
    {
        otherPlayer->hp = 0;
        return true;
    }

    otherPlayer->hp = otherPlayer->hp - this->damage;
    return false;
}

void Player::Print()
{
    std::cout << this->name << ": HP: " << this->hp << ", DMG: " << this->damage << '\n';
}

std::string Player::GetName()
{
    return this->name;
}