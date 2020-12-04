#include "HeroTextRenderer.h"

void HeroTextRenderer::render(const Game &game) const
{
    TextRenderer::renderOutput(game, true);
};