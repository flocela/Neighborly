#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"
#include "House.h"
#include <map>
#include <utility>

class City_Grid: public City
{
public:

    // Grid is a square grid.
    // How are addresses determined? Left to right, then down.
    // Example of grid with a width of 3:
    // 0  1  2
    // 3  4  5
    // 6  7  8
    // x runs from left to right.
    // y runs from top to bottom.
    // Line containing 0 and 2 addresses is the most north.
    // Line containing 0 and 6 addresses is the most west.
    // Houses adjacent to 4 are 0, 1, 2, 3, 5, 6, 7, 8.
    City_Grid (int width);
    City_Grid () = delete;
    City_Grid (const City_Grid& o) = default;
    City_Grid (City_Grid&& o) noexcept = default;
    City_Grid& operator= (const City_Grid& o) = default;
    City_Grid& operator=(City_Grid&& o) noexcept = default;
    ~City_Grid () noexcept = default;

    double getHeight() const override;
    double getWidth() const override;

    Coordinate getCoordinate (const int& address) const override;
    std::unordered_map<const House*, Coordinate> getCoordinatesPerHouse() const;

    double getDist ( const int& from_address,  const int& to_address) const override;

    double getDist (
        const double firstX,
        const double firstY,
        const double secondX,
        const double secondY
    ) const override ;

    std::unordered_set<const House*> getHousesWithinDistance (
        const House* house,
        double allowableDist
    ) const override;

    std::pair<int, int> getXRangeForAllowableDistanceToHouse (
        const House* house,
        double allowableDist
    ) const;
    
    std::pair<int, int> getYRangeForAllowableDistanceToHouse (
        const House* house,
        double allowableDist
    ) const;

    int getNumOfHouses() const override;
    std::vector<const House*> getHouses () const override;
    std::unordered_set<const House*> getHousesAdjacent (int address) const override;

private:
    int _width;
    int _minX = 0; // smallest x value
    int _minY = 0; // smallest y value
    int _maxX;     // largest x value
    int _maxY;     // largest y value
    
    std::vector<std::unique_ptr<House>> _houses;

    std::map<int, House*> _house_per_address;

    // holds the return values for teh getHousesWithinDistance method. That way
    // the results do not need to be calculated for every call.
    // holds an unordered list of houses that are within the allowable distance
    // per the house and the allowable distance.
    mutable std::map< std::pair<double, int>, std::unordered_set<const House*> >
        _houses_within_distance;

    mutable std::map<int, std::unordered_set<const House*>> _adjacent_houses_per_house_address;

    // Returns x value of @address
    int get_x (const int& address) const;

    // Returns y value of @address.
    int get_y (const int& address) const;

    // Returns a random house from @setOfHouses.
    const House* selectRandom (std::unordered_set<const House*>& setOfHouses) const;
};

#endif