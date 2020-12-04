#pragma once

#include "SVGRenderer.h"

class ObserverSVGRenderer : public SVGRenderer
{
public:
    void render(const Game &) const
    {
        SVGRenderer::renderOutput(false);
    };
};