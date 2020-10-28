
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
     * Dueling the players with each other and display the winner and the loser.
     */
    void Play();

    /**
     * Displays all player's current status.
     */
    void ShowPlayers() const;

    /**
     * Displays the winner and the victim.
     */
    void ShowWinnerAndVictim() const;

private:
    /**
     * Create a player from the arguments.
     * Select the correct arguments for the currnet player from the argument list.
     * @param argv Array of arguments.
     * @param nthPlayer Number of the current player.
     * @return Created Player instance.
     */
    Player getPlayer(char **argv, int nthPlayer) const;

    /**
     * Get other player determined by the current player.
     * @return Index of the other player.
     */
    unsigned short getOther() const;
};