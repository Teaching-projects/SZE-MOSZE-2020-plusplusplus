#pragma once

#include <string>

#include "Renderer.h"

/**
 * @class SVGRenderer
 *
 * Render the map to SVG image
 * Render processing class, does the real image generation
 * 
 * @author +++ Team
 *
 * @version 1.0
 *
 * @date 2020-12-04
 *
 * Created on: 2020-12-04
 *
*/
class SVGRenderer : public Renderer
{
protected:
    /**
     * File to be written
     */
    std::string outFile;

    /**
     * Render the game map to the file
     * @param withLightRadius if true, Hero light radius will be respected
     */
    void renderOutput(const Game &game, bool withLightRadius) const;

public:
    /**
     * Constructor to be initialized with an output filename
     * @param filename Output file
     */
    SVGRenderer(const std::string &filename) : outFile(filename){};
};