#ifndef CITY_H
#define CITY_H

#include <vector>
#include <set>
#include <memory>
#include "Coordinate.h"
#include "House.h"
#include <unordered_map>
#include <unordered_set>

class City
{
    public:
        enum CityType { grid }; // TODO do I use this enum?
        virtual ~City() = default;

        // Returns the number of addresses.
        virtual int getNumOfHouses() const = 0;

        virtual double getWidth() const = 0;

        // Returns all the houses in the city.
        virtual std::vector<const House*> getHouses () const = 0;

        virtual double getDist (
            const int& from_address, 
            const int& to_address
        ) const = 0;

        // Returns all houses adjacent to house.
        virtual std::set<const House*> getAdjacentHouses (int address) const = 0;

        // Returns all houses within distance except for @house.
        virtual std::unordered_set<const House*> getHousesWithinDistance (
            const House* house, 
            double distance,
            std::unordered_set<House*>& nearHouses,
            std::set<const House*> notOccupied
        ) const = 0;

        virtual void findHousesWithinDistance (
        const House* house,
        double allowableDist,
        std::unordered_set<const House*>& nearHouses
        ) const = 0;

        // Returns coordinate of house (x, y).
        virtual Coordinate getCoordinate(const int& address) const = 0;

        virtual std::unordered_map<const House*, Coordinate > getCoordinatesPerHouse() = 0;
};

#endif