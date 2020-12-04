#include "ObserverSVGRenderer.h"

void ObserverSVGRenderer::render(const Game &game) const
{
    SVGRenderer::renderOutput(game, false);
};