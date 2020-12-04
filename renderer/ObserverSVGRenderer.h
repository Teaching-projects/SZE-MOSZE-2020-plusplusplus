#pragma once

#include "SVGRenderer.h"

class ObserverSVGRenderer : public SVGRenderer
{
public:
    void render(const Game &game) const;
};