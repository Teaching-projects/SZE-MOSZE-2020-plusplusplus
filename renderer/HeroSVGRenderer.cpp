#include "HeroSVGRenderer.h"

void HeroSVGRenderer::render(const Game &game) const
{
    SVGRenderer::renderOutput(game, true);
};