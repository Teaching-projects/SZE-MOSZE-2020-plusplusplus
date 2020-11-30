#pragma once

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
    bool operator==(const Location &location)
    {
        return x == location.x && y == location.y;
    }
};