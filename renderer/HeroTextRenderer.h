#pragma once

#include "TextRenderer.h"

class HeroTextRenderer : public TextRenderer
{
public:
    void render(const Game &) const
    {
        TextRenderer::renderOutput(true);
    };
};