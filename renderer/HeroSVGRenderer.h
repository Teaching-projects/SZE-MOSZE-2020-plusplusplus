#pragma once

#include "SVGRenderer.h"

/**
 * @class HeroSVGRenderer
 *
 * Render the map to SVG, respecting the light radius for the player
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
class HeroSVGRenderer : public SVGRenderer
{
public:
    /**
     * Render the game map into SVG
     */
    void render(const Game &game) const;
};