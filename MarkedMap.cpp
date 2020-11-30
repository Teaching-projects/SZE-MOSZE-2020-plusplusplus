#include <algorithm>

#include "MarkedMap.h"

Location MarkedMap::getHeroPosition() const
{
    for (int y = 0; y < getHeight(); y++)
    {
        for (int x = 0; x < getWidth(); x++)
        {
            if (getFieldType(x, y) == FieldType::Hero)
            {
                return Location(x, y);
            }
        }
    }

    throw HeroNotFoundException();
}

std::vector<Location> MarkedMap::getMonsterPositions(char c) const
{
    std::vector<Location> list;

    for (int y = 0; y < getHeight(); y++)
    {
        for (int x = 0; x < getWidth(); x++)
        {
            if (getField(x, y) == c)
            {
                list.emplace_back(Location(x, y));
            }
        }
    }

    return list;
}