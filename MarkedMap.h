#pragma once
#pragma GCC diagnostic ignored "-Wenum-compare"

#include <vector>

#include "Map.h"
#include "Location.h"

/**
 * @class MarkedMap 
 * 
 * @brief It defines an extended Map, with Hero and Monster definition.
 * 
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-12-01
 * 
 * Created on: 2020-11-30
 * 
*/
class MarkedMap : public Map
{
public:
    /**
	 * Possible type of Map fields
	*/
    enum FieldType : char
    {
        Free = ' ', //< Empty field
        Wall = '#', //< Blocked field
        Hero = 'H', //< Hero position
    };

    /**
     * Constructor to load a new map with the given filename
     * @param fileName local map filename
     */
    explicit MarkedMap(const std::string &fileName) : Map(fileName){};

    /**
     * Get the placed hero position
     * @throw HeroNotFoundException if no hero placed on the map
     * @return the Location of the Hero
     */
    Location getHeroPosition() const;

    /**
     * Get a vector of the placed monsters with the given identifier number
     * @param c a number as a char in 0-9 range as monster identifier
     * @return vector of monster locations
     */
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