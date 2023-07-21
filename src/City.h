#ifndef CITY_H
#define CITY_H

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Coordinate.h"
#include "House.h"

// Holds the coordinates and addresses in a city.
class City
{

protected:
    City () = default;
    City (const City& o) = default;
    City (City&& o)noexcept = default;
    City& operator= (const City& o) = default;
    City& operator= (City&& o) noexcept = default;

public:
    virtual ~City () noexcept = default;

    // Returns largest distance between any two houses (inclusively) in y direction.
    virtual double getHeight() const = 0;
    
    // Returns largest distance between any two houses (inclusively) in x direction.
    virtual double getWidth() const = 0;

    // Returns house coordinate, (x, y).
    virtual Coordinate getCoordinate (const int& address) const = 0;

    virtual const std::unordered_map<const House*, Coordinate>* getCoordinatesPerHouse() const = 0;

    virtual double getDist (const int& from_address, const int& to_address) const = 0;

    // Returns houses within distance from house. Does not include the given house.
    virtual std::unordered_set<const House*> getHousesWithinDistance (
        const House* centralHouse,
        double allowableDist
    ) const = 0;

    // Returns total number of houses.
    virtual size_t getNumOfHouses () const = 0;

    // Returns all the houses in the city.
    virtual std::vector<const House*> getHouses () const = 0;

    // Returns all houses deemed to be adjacent to house with given address.
    virtual std::unordered_set<const House*> getHousesAdjacent (int address) const = 0;

    // Returns const pointer to map of adjacent houses per house.
    virtual const std::unordered_map<const House*, std::unordered_set<const House*>>* 
        getAdjacentHousesPerHouse () const = 0;
};

#endif