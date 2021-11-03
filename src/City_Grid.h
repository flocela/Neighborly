#ifndef CITY_GRID_H
#define CITY_GRID_H

#include "City.h"
#include <map>
#include <utility>
#include "House.h"
#include <memory>

class City_Grid: public City
{
    public:

        // _width is the width of the grid. The x axis goes from left to right.
        // The y axis goes from top to bottom. Houses are ordered north to south,
        // from west to east. For exampleA _width of 3 would result in
        // 0  3  6
        // 1  4  7
        // 2  5  8
        // Address 3 is 2 units away from address 5 in the y direction.
        // Address 1 is 2 units away from address 7 in the x direction.
        // Line containing 0 and 3 addresses is the most north.
        // Line containing 0 and 2 addresses is the most west.
    	City_Grid (int width);
        City_Grid () = delete;
        City_Grid (const City_Grid& o) = default;
        City_Grid (City_Grid&& o) noexcept = default;
        City_Grid& operator= (const City_Grid& o) = default;
        ~City_Grid () = default;

        int getSize() const override;

        std::vector<House*> getHouses () const override;
        
        double dist (
            const int& from_address, 
            const int& to_address
        ) const override;

        std::set<House*> getAdjacentHouses (House* house) const override;

        std::set<House*> getHousesWithinDistance (
            House* house, 
            double allowableDist
        ) const override;

        std::set<House*> getNumberOfUnoccupiedNearHouses (
            House* house,
            double allowableDistance,
            std::set<House*> notOccupied,
            int count
        ) const override;
        
        Coordinate getCoordinate (const int& address) const override;

        bool equals(const City_Grid& other) const;

    private:
        int _width;
        int _minX = 0;
        int _minY = 0;
        int _maxX;
        int _maxY;

        // Houses in _houses are in order from smallest addrest to largest address.
    	std::vector<std::unique_ptr<House>> _houses;

        std::map<int, House*> _addrToHouseMap;

        std::map<std::pair<int, double>, std::vector<int>> _within_dist_map;

        // Returns houses that are within a boxed area around @house.
        // Width and height of box are 2 x allowableDist. @house is at center.
        std::set<House*> getHousesWithinBoxedDistance (
            House* house,
            double allowableDist
        ) const;
        
        // Returns the x value of origX minus allowableDist, except if x value
        // is off the city map, then returns the most west x value on the map.
        int getMinXLine (int origX, int allowableDist) const;

        // Returns the x value of origX plus allowableDist, except if x value
        // is off the city map, then returns the most east x value on the map.
        int getMaxXLine (int origX, int allowableDist) const;

        // Returns the y value of origY minus allowableDist, except if y value
        // is off the city map, then returns the most north y value on the map.
        int getMinYLine (int origY, int allowableDist) const;

        // Returns the y value of origY plus allowableDist, except if y value
        // is off the city map, then returns the most south y value on the map.
        int getMaxYLine (int origY, int allowableDist) const;

        // Returns a random house from @setOfHouses.
        House* selectRandom (std::set<House*>& setOfHouses) const;
        
        // Returns x value of @address
        int get_x (const int& address) const;

        // Returns y value of @address.
        int get_y (const int& address) const;

};

#endif