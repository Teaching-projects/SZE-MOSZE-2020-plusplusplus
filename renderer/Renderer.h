#pragma once

#include <ostream>

#include "../Game.h"

class Game;

/**
 * @class Renderer
 *
 * Abstract base class for rendering.
 * 
 * @author +++ Team
 *
 * @version 1.0
 *
 * @date 2020-12-04
 *
 * Created on: 2020-12-04
 *
*/
class Renderer
{
protected:
    /**
     * Internal renderer function to be called able
     * to render with and without respecting the light radius property
     * @param game Current game state reference.
     * @param withLightRadius If true, Hero light radius will be calculated
     */
    virtual void renderOutput(const Game &game, bool withLightRadius) const = 0;

public:
    /**
     * Default constructor
     */
    Renderer(){};

    /**
     * Default destructor
     */
    virtual ~Renderer(){};

    /**
     * Render the game map using the reference,
     * in the child class style
     * @param game Current game state reference
     */
    virtual void render(const Game &game) const = 0;
};
