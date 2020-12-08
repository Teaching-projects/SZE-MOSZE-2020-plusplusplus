#include "ObserverTextRenderer.h"

void ObserverTextRenderer::render(const Game &game) const
{
    TextRenderer::renderOutput(game, false);
};