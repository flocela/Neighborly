#include "catch.hpp"
#include "../src/City_Grid.h"
#include "../src/House.h"
#include <iostream>

#include <math.h>
// g++ --std=c++17 -o runme ../src/City_Grid.cpp test_City_Grid.cpp test_main.o

TEST_CASE("getSize()")
{
    City_Grid city = City_Grid(6);
    REQUIRE( city.getSize() == 36 );
    REQUIRE( city.getHouses().size() == 36);
}

TEST_CASE("dist()")
{   // house[1] is at (0, 1) and house[28] is at (4, 4).
    City_Grid city = City_Grid(6);
    std::vector<House*> houses = city.getHouses();
    const int a1  = houses[1]->_address;
    const int a28 = houses[28]->_address;
    REQUIRE( city.dist(a1, a28) == sqrt( (3 * 3) + (4 * 4) ) );
}

TEST_CASE("getAdjacentHouses() for corner house (3 neighbors) ")
{
    City_Grid city = City_Grid(6);
    std::vector<House*> houses = city.getHouses();

    House* cornerHouse = houses[0]; // house[0] is at (0,0).
    std::set<House*> adjToCorner = city.getAdjacentHouses(cornerHouse);
    std::set<House*> actualAdjToCorner = {};
    actualAdjToCorner.insert(houses[1]);
    actualAdjToCorner.insert(houses[6]);
    actualAdjToCorner.insert(houses[7]);

    REQUIRE( adjToCorner == actualAdjToCorner );
}

TEST_CASE("getAdjacentHouses() for edge house (5 neighbors)")
{
    City_Grid city = City_Grid(6);
    std::vector<House*> houses = city.getHouses();

    House* edgeHouse = houses[12];
    std::set<House*> adjToEdgeHoues = city.getAdjacentHouses(edgeHouse);
    std::set<House*> actualAdj = {};
    actualAdj.insert(houses[6]);
    actualAdj.insert(houses[7]);
    actualAdj.insert(houses[13]);
    actualAdj.insert(houses[18]);
    actualAdj.insert(houses[19]);

    REQUIRE( adjToEdgeHoues == actualAdj );
}

TEST_CASE("getAdjacentHouses() for house in middle of grid (8 neighbors)")
{
    City_Grid city = City_Grid(6);
    std::vector<House*> houses = city.getHouses();

    House* house = houses[15];
    std::set<House*> adjToHouse = city.getAdjacentHouses(house);
    std::set<House*> actualAdj = {};
    actualAdj.insert(houses[8]);
    actualAdj.insert(houses[9]);
    actualAdj.insert(houses[10]);
    actualAdj.insert(houses[14]);
    actualAdj.insert(houses[16]);
    actualAdj.insert(houses[20]);
    actualAdj.insert(houses[21]);
    actualAdj.insert(houses[22]);

    REQUIRE( adjToHouse == actualAdj );
}

TEST_CASE("getHousesWithinDistance() distance is 2.1")
{
    City_Grid city = City_Grid(6);
    std::vector<House*> houses = city.getHouses();

    House* house = houses[19];
    std::set<House*> nearHouses = city.getHousesWithinDistance(house, 2.1);
    std::set<int> nearAddresses;
    for (House* house :nearHouses)
    {
        nearAddresses.insert(house->_address);
    }

    std::set<int> actualNearHouseAddresses = {};
    actualNearHouseAddresses.insert(houses[18]->_address);
    actualNearHouseAddresses.insert(houses[24]->_address);
    actualNearHouseAddresses.insert(houses[25]->_address);
    actualNearHouseAddresses.insert(houses[31]->_address);
    actualNearHouseAddresses.insert(houses[26]->_address);
    actualNearHouseAddresses.insert(houses[20]->_address);
    actualNearHouseAddresses.insert(houses[21]->_address);
    actualNearHouseAddresses.insert(houses[14]->_address);
    actualNearHouseAddresses.insert(houses[7]->_address);
    actualNearHouseAddresses.insert(houses[13]->_address);
    actualNearHouseAddresses.insert(houses[12]->_address);
    
    REQUIRE( nearAddresses == actualNearHouseAddresses );
}

TEST_CASE("getNumberOfUnoccupiedNearHouses() distance is 1")
{
    City_Grid city = City_Grid(6);
    std::vector<House*> houses = city.getHouses();
    std::set<House*> occupiedHouses;
    occupiedHouses.insert(houses[18]);
    occupiedHouses.insert(houses[20]);
    int count = 4;

    House* house = houses[19];
    std::set<House*> nearHouses = 
        city.getNumberOfUnoccupiedNearHouses(house, 1.0, occupiedHouses, count);

    std::set<House*> actualNearHouses = {};
    actualNearHouses.insert(houses[13]);
    actualNearHouses.insert(houses[25]);
    
    REQUIRE( nearHouses == actualNearHouses );
}

TEST_CASE("getCoordinate() for a given address")
{
    City_Grid city = City_Grid(6);
    REQUIRE(city.getCoordinate(0) == Coordinate(0,0));
    REQUIRE(city.getCoordinate(1) == Coordinate(0,1));
    REQUIRE(city.getCoordinate(27) == Coordinate(4,3));
}

TEST_CASE("equals()")
{
    City_Grid a = City_Grid(6);
    City_Grid b = City_Grid(6);
    City_Grid c = City_Grid(7);
    REQUIRE (a.equals(b));
    REQUIRE (!a.equals(c));
}