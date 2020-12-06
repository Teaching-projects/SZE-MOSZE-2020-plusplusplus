#pragma once

#include "SVGRenderer.h"

/**
 * @class ObserverSVGRenderer
 *
 * Render the board to SVG, the full map
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
class ObserverSVGRenderer : public SVGRenderer
{
public:
    /**
     * Default constructor
     * @param filename SVG file path to be created by renderer
     * @relatealso ObserverSVGRenderer::ObserverSVGRenderer()
     */
    explicit ObserverSVGRenderer(const std::string &filename) : SVGRenderer(filename){};

    /**
     * Render the game map to the svg file
     */
    void render(const Game &game) const override;
};