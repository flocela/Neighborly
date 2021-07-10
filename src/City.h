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

        // getSize() returns the number of addresses.
        virtual int getSize() const = 0;
        virtual std::vector<House*> getHouses () const = 0;
        virtual double dist (const int& from_address, const int& to_address) const = 0;
        virtual std::vector<House*> getAdjacentHouses(House* house) const = 0;
        // Does not include @address in resulting set.
        virtual std::set<House*> getNearHouses (House* house, double distance) const = 0;
        // Does not include @address in resulting set.
        virtual std::set<House*> getNearHouses (
            House* house,
            double distance,
            std::set<House*> occupied,
            int count
        ) const = 0;
        virtual int get_x (const int& address) const = 0;
        virtual int get_y (const int& address) const = 0;
        virtual Coordinate getCoordinate(const int& address) const = 0;
        //vector<CityType> citytypes{Grid, }
};

#endif