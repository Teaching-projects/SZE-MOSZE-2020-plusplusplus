#include "loop.h"

#include <iostream>

Loop::Loop(char **argv)
{
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        this->players.emplace_back(this->getPlayer(argv, i));
    }
}

void Loop::Play()
{
    const unsigned short victim = this->getOther();

    if (!this->players[this->currentPlayer].Attack(&this->players[victim]))
    {
        this->currentPlayer = this->getNextAttacker();
        this->Play();
    }
}

void Loop::ShowPlayers() const
{
    for (const auto &player : this->players)
    {
        player.Print();
    }
}

void Loop::ShowWinner() const
{
    std::cout << players[this->currentPlayer].GetName() << " wins. Remaining HP: " << players[this->currentPlayer].GetHP() << std::endl;
}

Player Loop::getPlayer(char **argv, int nthPlayer) const
{
    int start = 1 + nthPlayer;
    return Player::parseUnit(argv[start]);
}

unsigned short Loop::getOther() const
{
    return (this->currentPlayer + 1) % NUMBER_OF_PLAYERS;
}

unsigned short Loop::getNextAttacker() const
{
    if (players[this->currentPlayer].GetNextAttack() <= players[this->getOther()].GetNextAttack())
    {
        return this->currentPlayer;
    }
    else
    {
        return this->getOther();
    }
}