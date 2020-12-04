#pragma once

#include "TextRenderer.h"

class ObserverTextRenderer : public TextRenderer
{
public:
    ObserverTextRenderer() : TextRenderer(){};
    ObserverTextRenderer(std::ostream &output) : TextRenderer(output){};

    void render(const Game &game) const;
};