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
    Player *winner = this->players[this->currentPlayer].DuelWith(&this->players[this->getOther()]);
    if (winner != &this->players[currentPlayer])
    {
        currentPlayer = getOther();
    }
}

void Loop::ShowPlayers() const
{
    for (const auto &player : this->players)
    {
        player.Print(std::cout);
    }
}

void Loop::ShowWinnerAndVictim() const
{
    int victim = this->getOther();

    std::cout << players[this->currentPlayer].GetName() << " wins. ";
    players[this->currentPlayer].Print(std::cout);
    std::cout << " | ";
    players[victim].Print(std::cout);
    std::cout << std::endl;
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