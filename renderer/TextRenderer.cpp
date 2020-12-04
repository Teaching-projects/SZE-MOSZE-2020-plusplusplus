#include <ostream>

#include "TextRenderer.h"
#include "../Location.h"

void TextRenderer::renderOutput(const Game &game, bool withLightRadius) const
{
    const Location topLeft = Location::getCorner(Location::CornerType::TOP_LEFT, game.map, game.hero);
    const Location topRight = Location::getCorner(Location::CornerType::TOP_RIGHT, game.map, game.hero);
    const Location bottomLeft = Location::getCorner(Location::CornerType::BOTTOM_LEFT, game.map, game.hero);
    const Location bottomRight = Location::getCorner(Location::CornerType::BOTTOM_RIGHT, game.map, game.hero);

    // Top border
    *output << std::endl
            << icons.at(Icon::TOP_LEFT);
    for (int x = topLeft.x; x <= topRight.x; x++)
    {
        *output << icons.at(Icon::HORIZONTAL);
    }
    *output << icons.at(Icon::TOP_RIGHT) << std::endl;

    // Side borders and Game board
    for (int y = topLeft.y; y <= bottomLeft.y; y++)
    {
        *output << icons.at(Icon::VERTICAL);

        for (int x = topLeft.x; x <= bottomRight.x; x++)
        {
            if (game.hero != nullptr && game.hero->isAlive() && game.hero->getLocation() == Location(x, y))
            {
                *output << icons.at(Icon::HERO);
                continue;
            }

            const unsigned int monsterCountInField = game.getMonsterCountInField(x, y);
            if (monsterCountInField != 0)
            {
                *output << icons.at(monsterCountInField > 1 ? Icon::MONSTERS
                                                            : Icon::MONSTER);
            }
            else
            {
                *output << icons.at(game.map->getFieldType(x, y) == Map::Wall ? Icon::WALL_FIELD
                                                                              : Icon::FREE_FIELD);
            }
        }

        *output << icons.at(Icon::VERTICAL) << std::endl;
    }

    // Bottom border
    *output << icons.at(Icon::BOTTOM_LEFT);
    for (int x = bottomLeft.x; x <= bottomRight.x; x++)
    {
        *output << icons.at(Icon::HORIZONTAL);
    }
    *output << icons.at(Icon::BOTTOM_RIGHT) << std::endl;
}