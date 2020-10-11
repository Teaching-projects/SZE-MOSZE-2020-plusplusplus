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
    this->showWinner(this->players[this->currentPlayer].DuelWith(&this->players[this->getOther()]));
}

void Loop::ShowPlayers() const
{
    for (const auto &player : this->players)
    {
        player.Print(std::cout);
    }
}

void Loop::showWinner(Player player) const
{
    std::cout << player.GetName() << " wins. Remaining HP: " << player.GetHP() << std::endl;
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