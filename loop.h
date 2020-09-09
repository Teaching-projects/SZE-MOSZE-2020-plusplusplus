#pragma once

#include "player.h"

constexpr auto NUMBER_OF_PLAYERS = 2;

class Loop
{
    Player *players;
    unsigned short currentPlayer = 0;

public:
    explicit Loop(char **argv);
    void Play();
    void ShowPlayers();
    void ShowWinner();
};