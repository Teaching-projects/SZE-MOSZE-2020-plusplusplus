
#pragma once

#include "player.h"

#include <vector>

constexpr auto NUMBER_OF_PLAYERS = 2;

/**
 * @class Loop 
 * 
 * @brief The main engine of the RPG game.
 * 
 * It manages all the player in the game.
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-10-07
 * 
 * Created on: 2020-10-07
 * 
*/
class Loop
{
    /**
     Vector of the players.
     */
    std::vector<Player> players;

    /**
     * Index of the current player. Default is the first.
     */
    unsigned short currentPlayer = 0;

public:
    /**
     * Constructor of the Loop.
     * Create the player from the arguments.
     * @param argv Array of the program call arguments.
     */
    explicit Loop(char **argv);

    /**
     * Start the game.
     * Dueling the players with each other and display the winner.
     */
    void Play();

    /**
     * Displays all player's current status.
     */
    void ShowPlayers() const;

    /**
     * Displays the winner and victim.
     */
    void ShowWinnerAndVictim() const;

private:
    /**
     * Create the player from the arguments.
     * Get correct arguments for the correct player.
     * @param argv Array of arguments.
     * @param nthPlayer Number of the current creating player.
     * @return Created Player instance.
     */
    Player getPlayer(char **argv, int nthPlayer) const;

    /**
     * Get other player determined by the current player.
     * @return Index of the other player.
     */
    unsigned short getOther() const;
};