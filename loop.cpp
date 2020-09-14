#include "loop.h"

#include <iostream>

Loop::Loop(char** argv)
{
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        this->players.emplace_back(this->getPlayer(argv, i));
    }
}

void Loop::Play()
{
    int victim = this->getVictim();

    std::cout << this->players[this->currentPlayer].GetName() << " -> " << this->players[victim].GetName() << '\n';

    bool gameEnd = false;
    if (this->players[this->currentPlayer].Attack(&this->players[victim]))
    {
        gameEnd = true;
    }
    else
    {
        this->currentPlayer = victim;
    }

    this->ShowPlayers();

    if (!gameEnd)
    {
        this->Play();
    }
}

void Loop::ShowPlayers() const
{
    for (const auto& player : this->players)
    {
        player.Print();
    }
}

void Loop::ShowWinner() const
{
    std::cout << players[this->getVictim()].GetName() << " died. ";
    std::cout << players[this->currentPlayer].GetName() << " wins.\n";
}

Player Loop::getPlayer(char** argv, int nthPlayer) const
{
    int start = 1 + (nthPlayer * 3);
    return Player(argv[start], atoi(argv[start + 1]), atoi(argv[start + 2]));
}

unsigned short Loop::getVictim() const {
    return (this->currentPlayer + 1) % NUMBER_OF_PLAYERS;
}
