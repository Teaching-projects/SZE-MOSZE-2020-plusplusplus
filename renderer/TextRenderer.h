#pragma once

#include <ostream>

#include "Renderer.h"

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
    std::ostream *output = &std::cout;

    void renderOutput(const Game &game, bool withLightRadius) const;

public:
    TextRenderer(){};
    TextRenderer(std::ostream *output)
    {
        setOutputStream(output);
    };

    virtual void render(const Game &) const;
    void setOutputStream(std::ostream *output)
    {
        this->output = output;
    };
};
