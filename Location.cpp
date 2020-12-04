#include "Location.h"

Location Location::getCorner(CornerType type, Map *map, Hero *hero)

{
    int x = 0, y = 0;
    bool hasHero = hero != nullptr;
    const unsigned int range = hasHero ? hero->getLightRadius() : 0;
    const Location heroLoc = hasHero ? hero->getLocation() : Location(0, 0);
    const int heightIndex = map->getHeight() - 1;
    const int widthIndex = map->getWidth() - 1;

    switch (type)
    {
    case Location::CornerType::TOP_LEFT:
        return Location(!hasHero
                            ? 0
                            : (heroLoc.x - range) <= 0
                                  ? 0
                                  : (heroLoc.x - range),
                        !hasHero
                            ? 0
                            : (heroLoc.y - range) <= 0
                                  ? 0
                                  : (heroLoc.y - range));
        break;
    case Location::CornerType::TOP_RIGHT:
        return Location(!hasHero
                            ? widthIndex
                            : (heroLoc.x + range) >= widthIndex
                                  ? widthIndex
                                  : (heroLoc.x + range),
                        !hasHero
                            ? 0
                            : (heroLoc.y - range) <= 0
                                  ? 0
                                  : (heroLoc.y - range));
        break;
    case Location::CornerType::BOTTOM_LEFT:
        return Location(!hasHero
                            ? 0
                            : (heroLoc.x - range) <= 0
                                  ? 0
                                  : (heroLoc.x - range),
                        !hasHero
                            ? heightIndex
                            : (heroLoc.y + range) >= heightIndex
                                  ? heightIndex
                                  : (heroLoc.y + range));
        break;
    case Location::CornerType::BOTTOM_RIGHT:
        return Location(!hasHero
                            ? widthIndex
                            : (heroLoc.x + range) >= widthIndex
                                  ? widthIndex
                                  : (heroLoc.x + range),
                        !hasHero
                            ? heightIndex
                            : (heroLoc.y + range) >= heightIndex
                                  ? heightIndex
                                  : (heroLoc.y + range));
        break;
    }

    throw std::runtime_error("Unknown CornerType!");
}
