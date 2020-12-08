#pragma once

#include "TextRenderer.h"

/**
 * @class HeroTextRenderer
 *
 * Render the map to an output stream, respecting the light radius for the player
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
class HeroTextRenderer : public TextRenderer
{
public:
    /**
     * Default constructor, defaults to std::cout
     * @relatealso TextRenderer::TextRenderer()
     */
    HeroTextRenderer() : TextRenderer(){};

    /**
     * Set the output stream
     */
    explicit HeroTextRenderer(std::ostream &output) : TextRenderer(output){};

    /**
     * Render the game map to the stream
     */
    void render(const Game &game) const override;
};