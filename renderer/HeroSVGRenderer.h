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
     * Default constructor
     * @param filename SVG file path to be created by renderer
     * @relatealso ObserverSVGRenderer::ObserverSVGRenderer()
     */
    explicit HeroSVGRenderer(const std::string &filename) : SVGRenderer(filename){};

    /**
     * Render the game map into SVG
     */
    void render(const Game &game) const override;
};