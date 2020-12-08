#include "Corner.h"

Location Corner::Get(Type type, bool withLightRadius, const Game &game)
{
    withLightRadius = game.hero != nullptr && withLightRadius;
    const int range = withLightRadius ? game.hero->getLightRadius() : 0;
    const Location heroLoc = withLightRadius ? game.hero->getLocation() : Location(0, 0);
    const int heightIndex = game.map->getHeight() - 1;
    const int widthIndex = game.map->getWidth() - 1;

    switch (type)
    {
    case Type::TOP_LEFT:
        return Location(!withLightRadius
                            ? 0
                            : ((heroLoc.x - range) <= 0
                                   ? 0
                                   : (heroLoc.x - range)),
                        !withLightRadius
                            ? 0
                            : (heroLoc.y - range) <= 0
                                  ? 0
                                  : (heroLoc.y - range));
    case Type::TOP_RIGHT:
        return Location(!withLightRadius
                            ? widthIndex
                            : (heroLoc.x + range) >= widthIndex
                                  ? widthIndex
                                  : (heroLoc.x + range),
                        !withLightRadius
                            ? 0
                            : (heroLoc.y - range) <= 0
                                  ? 0
                                  : (heroLoc.y - range));
    case Type::BOTTOM_LEFT:
        return Location(!withLightRadius
                            ? 0
                            : (heroLoc.x - range) <= 0
                                  ? 0
                                  : (heroLoc.x - range),
                        !withLightRadius
                            ? heightIndex
                            : (heroLoc.y + range) >= heightIndex
                                  ? heightIndex
                                  : (heroLoc.y + range));
    case Type::BOTTOM_RIGHT:
        return Location(!withLightRadius
                            ? widthIndex
                            : (heroLoc.x + range) >= widthIndex
                                  ? widthIndex
                                  : (heroLoc.x + range),
                        !withLightRadius
                            ? heightIndex
                            : (heroLoc.y + range) >= heightIndex
                                  ? heightIndex
                                  : (heroLoc.y + range));
    }

    throw std::runtime_error("Unknown CornerType!");
}