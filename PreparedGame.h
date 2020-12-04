#pragma once

#include "Game.h"
#include "MarkedMap.h"
#include "renderer/Renderer.h"

/**
 * @class PreparedGame 
 * 
 * @brief It defines an extended Game, loading a prepared game definition, with MarkedMap.
 * 
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-12-01
 * 
 * Created on: 2020-11-30
 * 
*/
class PreparedGame : private Game
{
private:
public:
    /**
     * Constructor to set up game with the prepare data file
     * Loads the map, the Hero and the Monsters
     * 
     * @param file prepare data file
     */
    explicit PreparedGame(const std::string &file);

    /**
     * Run the game, in loop
     * @relatealso Game::run
     */
    void run();

    /**
     * Register a renderer class to print the game state
     * @relatealso Game::registerRenderer
     */
    void registerRenderer(Renderer *renderer);
};
