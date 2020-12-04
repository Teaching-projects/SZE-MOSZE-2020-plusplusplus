#pragma once

#include "SVGRenderer.h"

class HeroSVGRenderer : public SVGRenderer
{
public:
    void render(const Game &) const
    {
        SVGRenderer::renderOutput(true);
    };
};