#pragma once

#include "TextRenderer.h"

class ObserverTextRenderer : public TextRenderer
{
public:
    void render(const Game &) const
    {
        TextRenderer::renderOutput(false);
    };
};