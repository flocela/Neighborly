#ifndef CITY_H
#define CITY_H

#include <vector>
#include <set>
#include <memory>
#include "Coordinate.h"
#include "House.h"

class City
{
    public:
        enum CityType { grid };
        virtual ~City() = default;

        // Returns the number of addresses.
        virtual int getSize() const = 0;

        // Returns all the houses in the city.
        virtual std::vector<House*> getHouses () const = 0;

        virtual double dist (
            const int& from_address, 
            const int& to_address
        ) const = 0;

        // Returns all houses considered to be adjacent by city.
        virtual std::set<House*> getAdjacentHouses(House* house) const = 0;

        // Returns all houses within distance except for @house.
        virtual std::set<House*> getHousesWithinDistance (
            House* house, 
            double distance
        ) const = 0;

        // Returns @count number of unoccupied houses that are not
        // occupied as determined by @occupied and within @distance.
        // May return less than @count houses because there are not
        // @count number of houses that are unoccupied and within @distance.
        // @house not included in returned set.
        virtual std::set<House*> getNumberOfUnoccupiedNearHouses (
            House* house,
            double distance,
            std::set<House*> occupied,
            int count
        ) const = 0;

        // Returns coordinate of house (x, y).
        virtual Coordinate getCoordinate(const int& address) const = 0;

        // returns most east x coordinate.
        virtual int getLargestXCoord () const = 0;

        // returns most south coordinate.
        virtual int getLargestYCoord () const = 0;

        // returns house with largest address.
        virtual int getLargestAddress () const = 0;
};

#endif