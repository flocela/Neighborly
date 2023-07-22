#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"
#include <map>

// Only has getter functions.
// Can not change city's coordinates or addresses after construction.
class City_Grid: public City
{
public:

    // Grid is a square grid that names addresses left to right, then down.
    // Example of grid with a width of 3:
    // 0  1  2
    // 3  4  5
    // 6  7  8
    // x runs from left to right.
    // y runs from top to bottom.
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
    const std::unordered_map<const House*, Coordinate>* getCoordinatesPerHouse() const;

    double getDist ( const int& from_address,  const int& to_address) const override;

    std::unordered_set<const House*> getHousesWithinDistance (
        const House* centralHouse,
        double allowableDist
    ) const override;

    size_t getNumOfHouses() const override;
    std::vector<const House*> getHouses () const override;

    // Returns houses that are adjacent to the house corresponding to the given address. For a
    // house that is not on an edge, that is 8 houses.
    std::unordered_set<const House*> getHousesAdjacent (int address) const override;

    const SetOfHousesPerHouse* getAdjacentHousesPerHouse () const override;

private:
    int _width;
    int _minX = 0; // smallest x coordinate
    int _minY = 0; // smallest y coordinate
    int _maxX;     // largest x coordinate
    int _maxY;     // largest y coordinate
    
    std::vector<std::unique_ptr<House>> _houses;

    std::unordered_map<int, House*> _house_per_address;

    std::unordered_map<const House*, Coordinate> _coordinates_per_house{};

    // Holds the return values for the getHousesWithinDistance method. That way
    // the results do not need to be recalculated for every call.
    // Holds an unordered list of houses that are within the allowable distance
    // per the house and the allowable distance.
    mutable std::map< std::pair<double, int>, std::unordered_set<const House*> >
        _houses_within_distance;

    SetOfHousesPerHouse _adjacent_houses_per_house{};

    // Returns x value of @address
    int get_x (const int& address) const;

    // Returns y value of @address.
    int get_y (const int& address) const;
};

#endif