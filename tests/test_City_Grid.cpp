#include "catch.hpp"
#include "../src/Coordinate.h"
#include "../src/City_Grid.h"
#include "../src/House.h"
#include <iostream>

#include <math.h>

using namespace std;

TEST_CASE("getSize()")
{
    City_Grid city = City_Grid(6);
    REQUIRE( city.getNumOfHouses() == 36 );
    REQUIRE( city.getHouses().size() == 36);
}

TEST_CASE("GetCoordinate()")
{
    City_Grid city = City_Grid(6);
    Coordinate coord = city.getCoordinate(13);
    REQUIRE( coord.getX() == 1 ); //1
    REQUIRE( coord.getY() == 2 ); //2
}

TEST_CASE("dist()")
{   // house[1] is at (0, 1) and house[28] is at (4, 4).
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();
    const int a1  = houses[1]->getAddress();
    const int a28 = houses[28]->getAddress();
    REQUIRE( sqrt( (3 * 3) + (4 * 4) ) == city.getDist(a1, a28) ); // 
}

TEST_CASE("getHousesWithinDistance() distance is 2.1, central house, all houses open")
{
    City_Grid city = City_Grid(6);

    vector<const House*> houses = city.getHouses();

    unordered_set<const House*> cityHouses{};
    for (const House* h : houses)
    {
        cityHouses.insert(h);
    }

    const House* house = houses[19];
    unordered_set<const House*> actualHouses = 
        city.getHousesWithinDistance(house, 2.1, 2);

    unordered_set<int> actualAddresses;
    for (const House* house :actualHouses)
    {
        actualAddresses.insert(house->getAddress());
    }

    unordered_set<int> expectedAddresses = {};
    expectedAddresses.insert(houses[18]->getAddress());
    expectedAddresses.insert(houses[24]->getAddress());
    expectedAddresses.insert(houses[25]->getAddress());
    expectedAddresses.insert(houses[31]->getAddress());
    expectedAddresses.insert(houses[26]->getAddress());
    expectedAddresses.insert(houses[20]->getAddress());
    expectedAddresses.insert(houses[21]->getAddress());
    expectedAddresses.insert(houses[14]->getAddress());
    expectedAddresses.insert(houses[7]->getAddress());
    expectedAddresses.insert(houses[13]->getAddress());
    expectedAddresses.insert(houses[12]->getAddress());
    
    REQUIRE( expectedAddresses == actualAddresses );
}

TEST_CASE("getHousesWithinDistance() distance is 2.1, house at side, all houses open")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    unordered_set<const House*> cityHouses{};
    for (const House* h : houses)
    {
        cityHouses.insert(h);
    }

    const House* house = houses[18];
    unordered_set<const House*> actualHouses = 
        city.getHousesWithinDistance(house, 2.1, 2);

    unordered_set<int> actualAddresses;
    for (const House* house :actualHouses)
    {
        actualAddresses.insert(house->getAddress());
    }

    unordered_set<int> expectedAddresses = {};
    expectedAddresses.insert(houses[6]->getAddress());
    expectedAddresses.insert(houses[12]->getAddress());
    expectedAddresses.insert(houses[13]->getAddress());
    expectedAddresses.insert(houses[19]->getAddress());
    expectedAddresses.insert(houses[20]->getAddress());
    expectedAddresses.insert(houses[24]->getAddress());
    expectedAddresses.insert(houses[25]->getAddress());
    expectedAddresses.insert(houses[30]->getAddress());
    
    REQUIRE( expectedAddresses == actualAddresses );
}

TEST_CASE("getHousesWithinDistance() distance is 2.1, central house, some houses open")
{
    City_Grid city = City_Grid(6);

    vector<const House*> houses = city.getHouses();

    const House* house = houses[19];
    unordered_set<const House*> actualHouses = 
        city.getHousesWithinDistance(house, 2.1, 2);

    unordered_set<int> actualAddresses;
    for (const House* house :actualHouses)
    {
        actualAddresses.insert(house->getAddress());
    }

    unordered_set<int> expectedAddresses = {};
    expectedAddresses.insert(houses[12]->getAddress());
    expectedAddresses.insert(houses[18]->getAddress());
    expectedAddresses.insert(houses[24]->getAddress());
    expectedAddresses.insert(houses[7]->getAddress());
    expectedAddresses.insert(houses[13]->getAddress());
    expectedAddresses.insert(houses[25]->getAddress());
    expectedAddresses.insert(houses[31]->getAddress());
    expectedAddresses.insert(houses[14]->getAddress());
    expectedAddresses.insert(houses[20]->getAddress());
    expectedAddresses.insert(houses[26]->getAddress());
    expectedAddresses.insert(houses[21]->getAddress());
    
    REQUIRE( expectedAddresses == actualAddresses );
}

TEST_CASE("getHousesAdjacent() for corner house (3 neighbors) ")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    const House* cornerHouse = houses[0]; // house[0] is at (0,0).

    unordered_set<const House*> actualNeighbors = city.getHousesAdjacent(cornerHouse->getAddress());
    unordered_set<const House*> expectedNeighbors = {};
    expectedNeighbors.insert(houses[1]);
    expectedNeighbors.insert(houses[6]);
    expectedNeighbors.insert(houses[7]);

    REQUIRE( expectedNeighbors == actualNeighbors );
}

TEST_CASE("getAdjacentHouses() for left edge house (5 neighbors)")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    const House* edgeHouse = houses[12];
    unordered_set<const House*> actualNeighbors = city.getHousesAdjacent(edgeHouse->getAddress());
    unordered_set<const House*> expectedNeighbors = {};
    expectedNeighbors.insert(houses[6]);
    expectedNeighbors.insert(houses[7]);
    expectedNeighbors.insert(houses[13]);
    expectedNeighbors.insert(houses[18]);
    expectedNeighbors.insert(houses[19]);

    REQUIRE( expectedNeighbors == actualNeighbors );
}

TEST_CASE("getAdjacentHouses() for right edge house (5 neighbors)")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    const House* edgeHouse = houses[29];
    unordered_set<const House*> actualNeighbors = city.getHousesAdjacent(edgeHouse->getAddress());
    unordered_set<const House*> expectedNeighbors = {};
    expectedNeighbors.insert(houses[22]);
    expectedNeighbors.insert(houses[23]);
    expectedNeighbors.insert(houses[28]);
    expectedNeighbors.insert(houses[34]);
    expectedNeighbors.insert(houses[35]);

    REQUIRE( expectedNeighbors == actualNeighbors );
}

TEST_CASE("getAdjacentHouses() for top edge house (5 neighbors)")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    const House* edgeHouse = houses[4];
    unordered_set<const House*> actualNeighbors = city.getHousesAdjacent(edgeHouse->getAddress());
    unordered_set<const House*> expectedNeighbors = {};
    expectedNeighbors.insert(houses[3]);
    expectedNeighbors.insert(houses[9]);
    expectedNeighbors.insert(houses[10]);
    expectedNeighbors.insert(houses[11]);
    expectedNeighbors.insert(houses[5]);

    REQUIRE( expectedNeighbors == actualNeighbors );
}

TEST_CASE("getAdjacentHouses() for bottom edge house (5 neighbors)")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    const House* edgeHouse = houses[31];
    unordered_set<const House*> actualNeighbors = city.getHousesAdjacent(edgeHouse->getAddress());
    unordered_set<const House*> expectedNeighbors = {};
    expectedNeighbors.insert(houses[24]);
    expectedNeighbors.insert(houses[25]);
    expectedNeighbors.insert(houses[26]);
    expectedNeighbors.insert(houses[30]);
    expectedNeighbors.insert(houses[32]);

    REQUIRE( expectedNeighbors == actualNeighbors );
}

TEST_CASE("getAdjacentHouses() for house in middle of grid (8 neighbors)")
{
    City_Grid city = City_Grid(6);
    vector<const House*> houses = city.getHouses();

    const House* house = houses[15];
    unordered_set<const House*> actualNeighbors = city.getHousesAdjacent(house->getAddress());
    unordered_set<const House*> expectedNeighbors = {};
    expectedNeighbors.insert(houses[8]);
    expectedNeighbors.insert(houses[9]);
    expectedNeighbors.insert(houses[10]);
    expectedNeighbors.insert(houses[14]);
    expectedNeighbors.insert(houses[16]);
    expectedNeighbors.insert(houses[20]);
    expectedNeighbors.insert(houses[21]);
    expectedNeighbors.insert(houses[22]);

    REQUIRE( expectedNeighbors == actualNeighbors );
}

TEST_CASE("getCoordinate() for a given address")
{
    City_Grid city = City_Grid(6);
    REQUIRE(Coordinate(0, 0) == city.getCoordinate(0)); // 0, 0
    REQUIRE(Coordinate(1, 0) == city.getCoordinate(1)); // 1, 0
    REQUIRE(Coordinate(3, 4) == city.getCoordinate(27));// 3, 4
}