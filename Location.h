#pragma once

/**
 * @class Location 
 * 
 * @brief It defines a simple 2d location object.
 * 
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-12-01
 * 
 * Created on: 2020-11-28
 * 
*/
class Location
{
public:
    /**
     * The X coordinate of the location.
     */
    int x;

    /**
     * The Y coordinate of the location.
     */
    int y;

    /**
     * Constructor of the location.
     */
    Location(){};

    /**
     * Constructor of the location.
     * @param x The X coordinate
     * @param y The Y coordinate
     */
    Location(int x, int y) : x(x), y(y){};

    /**
     * The equal operator.
     * @param location The other Location object
     */
    bool operator==(const Location &location) const
    {
        return x == location.x && y == location.y;
    }
};