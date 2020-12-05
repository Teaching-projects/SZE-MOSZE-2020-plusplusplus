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
    explicit ObserverSVGRenderer(const std::string &filename) : SVGRenderer(filename){};

    void render(const Game &game) const override;
};