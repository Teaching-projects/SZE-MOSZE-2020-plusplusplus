#pragma once

#include <ostream>

#include "Renderer.h"

/**
 * @class TextRenderer
 *
 * Render the map to an output stream
 * Render processing class, writes to the stream
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
class TextRenderer : public Renderer
{
    /**
	 * Enum type for the gameboard icon definitions.
	 */
    enum Icon
    {
        TOP_LEFT,
        TOP_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_RIGHT,
        HORIZONTAL,
        VERTICAL,
        FREE_FIELD,
        WALL_FIELD,
        HERO,
        MONSTER,
        MONSTERS
    };
    /**
	 * Type definition for the mapped Icons.
	 */
    typedef std::map<Icon, std::string> iconKeyMap;
    /**
	 * The Icons mapped with their key.
	 */
    inline static const iconKeyMap icons = {
        {Icon::TOP_LEFT, "\u2554"},
        {Icon::TOP_RIGHT, "\u2557"},
        {Icon::BOTTOM_LEFT, "\u255A"},
        {Icon::BOTTOM_RIGHT, "\u255D"},
        {Icon::HORIZONTAL, "\u2550\u2550"},
        {Icon::VERTICAL, "\u2551"},
        {Icon::FREE_FIELD, "\u2591\u2591"},
        {Icon::WALL_FIELD, "\u2588\u2588"},
        {Icon::HERO, "\u2523\u252B"},
        {Icon::MONSTER, "\u004D\u2591"},
        {Icon::MONSTERS, "\u004D\u004D"}};

protected:
    /**
     * Output stream to be written
     */
    std::ostream *output = &std::cout;

    /**
     * Print the game state to the stream
     * @param withLightRadius if true, Hero light radius will be respected
     */
    void renderOutput(const Game &game, bool withLightRadius) const override;

public:
    /**
     * Default constructor, writes to std::cout
     */
    TextRenderer(){};

    /**
     * Constructor, set a custom stream for output
     */
    explicit TextRenderer(std::ostream &output)
    {
        setOutputStream(output);
    };

    /**
     * Set the output stream
     */
    void setOutputStream(std::ostream &output)
    {
        this->output = &output;
    };
};
