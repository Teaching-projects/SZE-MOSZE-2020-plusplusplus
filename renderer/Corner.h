#pragma once

#include "../Location.h"
#include "../Game.h"

/**
 * @class Corner
 *
 * Get the location of the corners around the board
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
class Corner
{
public:
    /**
	 * Enum type for light range corner detection.
	 */
    enum Type
    {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    };

    /**
     * Get the corner location
     * @param type corner side
     * @param withLightRadius only get the part visible for the hero (if placed)
     * @param game game board reference
     */
    static Location Get(Type type, bool withLightRadius, const Game &game);
};