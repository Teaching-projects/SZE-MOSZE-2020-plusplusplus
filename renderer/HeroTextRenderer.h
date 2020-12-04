#pragma once

#include "TextRenderer.h"

class HeroTextRenderer : public TextRenderer
{
public:
    HeroTextRenderer() : TextRenderer(){};
    HeroTextRenderer(std::ostream &output) : TextRenderer(output){};

    void render(const Game &game) const;
};