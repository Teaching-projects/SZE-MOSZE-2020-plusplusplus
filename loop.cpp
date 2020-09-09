#include "loop.h"

#include <iostream>

Loop::Loop(char **argv)
{
    this->players = new Player[NUMBER_OF_PLAYERS]();
    for (unsigned short i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        this->players[i].Read(argv, i);
    }
}

void Loop::Play()
{
    int victim = this->currentPlayer + 1 < NUMBER_OF_PLAYERS ? this->currentPlayer + 1 : 0;

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
    std::cout << '\n';

    if (!gameEnd)
    {
        this->Play();
    }
}

void Loop::ShowPlayers()
{
    for (unsigned short i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        this->players[i].Print();
    }
}

void Loop::ShowWinner()
{
    int victim = this->currentPlayer + 1 < NUMBER_OF_PLAYERS ? this->currentPlayer + 1 : 0;

    std::cout << this->players[victim].GetName() << " died. ";
    std::cout << this->players[this->currentPlayer].GetName() << " wins.\n";
}