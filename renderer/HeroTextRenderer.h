#pragma once

#include "TextRenderer.h"

class HeroTextRenderer : public TextRenderer
{
public:
    void render(const Game &game) const
    {
        TextRenderer::renderOutput(game, true);
    };
};