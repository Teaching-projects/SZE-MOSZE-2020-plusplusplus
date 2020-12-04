#pragma once

#include <string>

#include "Renderer.h"

class SVGRenderer : public Renderer
{
protected:
    std::string outFile;

    void renderOutput(const Game &game, bool withLightRadius) const;

public:
    SVGRenderer(const std::string &filename) : outFile(filename){};
};