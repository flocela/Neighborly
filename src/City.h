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
    // largest distance between any two houses (inclusively) in y direction.
    virtual double getHeight() const = 0;
    
    // largest distance between any two houses (inclusively) in x direction.
    virtual double getWidth() const = 0;

    // Returns coordinate of house (x, y).
    virtual Coordinate getCoordinate(const int& address) const = 0;

    virtual std::unordered_map<const House*, Coordinate > getCoordinatesPerHouse() = 0;

    virtual double getDist (
        const int& from_address, 
        const int& to_address
    ) const = 0;

    virtual std::unordered_set<const House*> getHousesWithinDistance (
        const House* house,
        double allowableDist
    ) const = 0;

    // total number of addresses. same as total number of houses.
    virtual int getNumOfHouses() const = 0;

    // Returns all the houses in the city.
    virtual std::vector<const House*> getHouses () const = 0;

    // Returns all houses adjacent to address of house.
    virtual std::set<const House*> getHousesAdjacent (int address) const = 0;

    // Returns a string representing the city. Characters will represent specific addresses.
    virtual std::string toString (const std::unordered_map<int, char>& characterPerAddress) = 0;
};

#endif