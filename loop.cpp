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

    for (unsigned short i = 0; i < NUMBER_OF_PLAYERS; i++)
    {
        this->players[i].Print();
    }

    if (!gameEnd)
    {
        this->Play();
    }
}

void Loop::ShowWinner()
{
    std::cout << this->players[this->getVictim()].GetName() << " died. ";
    std::cout << this->players[this->currentPlayer].GetName() << " wins.\n";
}

unsigned short Loop::getVictim() {
	return this->currentPlayer + 1 < NUMBER_OF_PLAYERS ? this->currentPlayer + 1 : 0;
}
