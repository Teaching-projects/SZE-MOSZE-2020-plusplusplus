#pragma once

#include "player.h"

#include <vector>

constexpr auto NUMBER_OF_PLAYERS = 2;

class Loop
{
    std::vector<Player> players;
    unsigned short currentPlayer = 0;

public:
    explicit Loop(char** argv);
    void Play();
    void ShowPlayers() const;
    void ShowWinner() const;

private:
    Player getPlayer(char** argv, int nthPlayer);
    unsigned short getVictim() const;
};