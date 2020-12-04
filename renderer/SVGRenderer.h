#pragma once

#include <string>

#include "Renderer.h"

class SVGRenderer : public Renderer
{
protected:
    std::string outFile;

    void renderOutput(bool withLightRadius) const;

public:
    SVGRenderer(const std::string &filename) : outFile(filename){};
};