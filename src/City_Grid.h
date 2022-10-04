#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"
#include <map>
#include "House.h"

class City_Grid: public City
{
public:

    // _width is the width of the square grid.
    // For exampleA _width of 3 would result in
    // 0  1  2
    // 3  4  5
    // 6  7  8
    // Address 3 is 2 units away from address 5 in the x direction.
    // Address 1 is 2 units away from address 7 in the y direction.
    // Line containing 0 and 2 addresses is the most north.
    // Line containing 0 and 6 addresses is the most west.
    // Houses adjacent to 4 are 0, 1, 2, 3, 5, 6, 7, 8.
    City_Grid (int width);
    City_Grid () = delete;
    City_Grid (const City_Grid& o) = default;
    City_Grid (City_Grid&& o) noexcept = default;
    City_Grid& operator= (const City_Grid& o) = default;
    ~City_Grid () = default;

    int getNumOfHouses() const override;

    Coordinate getCoordinate (const int& address) const override;

    double getDist ( const int& from_address,  const int& to_address) const override;

    std::vector<const House*> getHouses () const override;
    
    std::set<const House*> getAdjacentHouses (const House* house) const override;

    //TODO only used in SimulatorE, so if SimulatorE is deleted, then delete this method.
    std::set<House*> getHousesWithinDistance (
        const House* house, 
        double allowableDist
    ) const override;

    std::set<const House*> getANumberOfUnoccupiedNearHouses (
        const House* house,
        double allowableDistance,
        std::set<const House*> notOccupied,
        size_t count
    ) const override;
    
    std::unordered_map<const House*, Coordinate> getCoordinatesPerHouse();

private:
    int _width;
    int _minX = 0;
    int _minY = 0;
    int _maxX;
    int _maxY;

    // Houses are in order. [0, 1, 2, 3, 4, 5, 6, 7, 8] for a grid
    // 0  1  2
    // 3  4  5
    // 6  7  8
    std::vector<std::unique_ptr<House>> _houses;

    std::map<int, House*> _house_per_address;

    //TODO try to use _within_dist_map
    std::map<std::pair<int, double>, std::vector<int>> _within_dist_map;

    // Returns a random house from @setOfHouses.
    House* selectRandom (std::set<House*>& setOfHouses) const;
    
    // Returns x value of @address
    int get_x (const int& address) const;

    // Returns y value of @address.
    int get_y (const int& address) const;

};

#endif