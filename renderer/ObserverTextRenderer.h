#pragma once

#include "TextRenderer.h"

class ObserverTextRenderer : public TextRenderer
{
public:
    void render(const Game &game) const
    {
        TextRenderer::renderOutput(game, false);
    };
};