#pragma once

#include <vector>

#include "Map.h"
#include "Location.h"

class MarkedMap : public Map
{
public:
    /**
	 * @enum Possible type of Map fields
	*/
    enum FieldType : char
    {
        Free = ' ',
        Wall = '#',
        Hero = 'H',
    };
    explicit MarkedMap(const std::string &fileName) : Map(fileName){};
    Location getHeroPosition() const;
    std::vector<Location> getMonsterPositions(char c) const;

    /**
	 * @class HeroNotFoundException
	 * @brief Hero is not place on the map while trying to get its position 
	*/
    class HeroNotFoundException : virtual public std::runtime_error
    {
    public:
        /**
		 * Constructor.
		*/
        explicit HeroNotFoundException() : std::runtime_error("Hero cannot be found on the map") {}
    };
};