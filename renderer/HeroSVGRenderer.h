#pragma once

#include "SVGRenderer.h"

class HeroSVGRenderer : public SVGRenderer
{
public:
    void render(const Game &game) const
    {
        SVGRenderer::renderOutput(game, true);
    };
};