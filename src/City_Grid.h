#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"
#include <map>
#include "House.h"

class City_Grid: public City
{
public:
    // Grid is a square grid.
    // Example of address counting is as follows:
    //  _width of 3 would result in
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
    ~City_Grid () = default;

    int getNumOfHouses() const override;

    double getWidth() const override;

    double getHeight() const override;

    Coordinate getCoordinate (const int& address) const override;

    double getDist ( const int& from_address,  const int& to_address) const override;

    std::vector<const House*> getHouses () const override;
    
    std::set<const House*> getAdjacentHouses (int address) const override;

    //TODO only used in SimulatorE, so if SimulatorE is deleted, then delete this method.
    //If not then check this method.
    std::unordered_set<const House*> getHousesWithinDistance (
        const House* house, 
        double allowableDist,
        std::unordered_set<House*>& nearHouses,
        std::set<const House*> notOccupied
    ) const override;

    // TODO shouldn't be using a refernce to get houses. Should return them.
    void findHousesWithinDistance (
        const House* house,
        double allowableDist,
        std::unordered_set<const House*>& nearHouses
    ) const override;
    
    std::unordered_map<const House*, Coordinate> getCoordinatesPerHouse();

private:
    int _width;
    int _minX = 0; // smallest x value
    int _minY = 0; // smallest y value
    int _maxX;     // largest x value
    int _maxY;     // largest y value
    
    std::vector<std::unique_ptr<House>> _houses;

    std::map<int, House*> _house_per_address;

    // Returns a random house from @setOfHouses.
    const House* selectRandom (std::unordered_set<const House*>& setOfHouses) const;
    
    // Returns x value of @address
    int get_x (const int& address) const;

    // Returns y value of @address.
    int get_y (const int& address) const;

};

#endif