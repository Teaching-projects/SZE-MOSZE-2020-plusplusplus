#pragma once

#include "TextRenderer.h"

/**
 * @class ObserverTextRenderer
 *
 * Render the map to Text, the full map.
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
class ObserverTextRenderer : public TextRenderer
{
public:
    /**
     * Default constructor, defaults to std::cout
     * @relatealso TextRenderer::TextRenderer()
     */
    ObserverTextRenderer() : TextRenderer(){};

    /**
     * Set the output stream
     */
    explicit ObserverTextRenderer(std::ostream &output) : TextRenderer(output){};

    /**
     * Render the game map to the stream
     */
    void render(const Game &game) const override;
};