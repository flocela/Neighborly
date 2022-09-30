#ifndef CITY_H
#define CITY_H

#include <vector>
#include <set>
#include <memory>
#include "Coordinate.h"
#include "House.h"
#include <unordered_map>

class City
{
    public:
        enum CityType { grid };
        virtual ~City() = default;

        // Returns the number of addresses.
        virtual int getNumOfHouses() const = 0;

        // Returns all the houses in the city.
        virtual std::vector<const House*> getHouses () const = 0;

        virtual double getDist (
            const int& from_address, 
            const int& to_address
        ) const = 0;

        // Returns all houses considered to be adjacent by city.
        virtual std::set<const House*> getAdjacentHouses (const House* house) const = 0;

        // Returns all houses within distance except for @house.
        virtual std::set<House*> getHousesWithinDistance (
            const House* house, 
            double distance
        ) const = 0;

        // Returns @count number of unoccupied houses that are not
        // occupied as determined by @occupied and within @distance.
        // May return less than @count houses because there are not
        // @count number of houses that are unoccupied and within @distance.
        // @house not included in returned set.
        virtual std::set<const House*> getANumberOfUnoccupiedNearHouses (
            const House* house,
            double distance,
            std::set<const House*> occupied,
            size_t count
        ) const = 0;

        // Returns coordinate of house (x, y).
        virtual Coordinate getCoordinate(const int& address) const = 0;

        virtual std::unordered_map<const House*, Coordinate > getCoordinatesPerHouse() = 0;
};

#endif