#pragma once

#include "../Location.h"
#include "../Game.h"

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

    static Location Get(Type type, bool withLightRadius, const Game &game);
};