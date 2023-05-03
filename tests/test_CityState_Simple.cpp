#include "catch.hpp"

#include "../src/CityState_Simple.h"
#include "../src/HappinessFunc_Flat.h" // TODO delete, only here for testing that a test works at all
#include "../src/Resident_UsingFunction.h" // TODO delete
#include "../src/City_Grid.h"

//TODO these have to be bigger grids!
/*TEST_CASE("empty city - getOpenHousesWithinRange() limited range")
{
    City_Grid city = City_Grid(10);
    CityState_Simple cityState{&city};

    // houses within rangeX 1:5 and rangeY 3:5
    std::vector<int> expected{};
    std::vector<const House*> houses = city.getHouses();
    for (const House* h : houses)
    {
        Coordinate coord = city.getCoordinate(h->getAddress());
        if (coord.getX() >= 1 && coord.getX() <=5 &&
            coord.getY() >= 3 && coord.getY() <= 5)
        {
            expected.push_back(h->getAddress());
        }
    }

    // actual
    std::vector<int> actual{};
    std::unordered_set<const House*> actualHousesInRange = 
        cityState.getOpenHousesWithinRange(1,5,3,5);
    for (const House* h : actualHousesInRange)
    {
        actual.push_back(h->getAddress());
    }

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

    REQUIRE(expected == actual);
}

TEST_CASE("empty city - getResidentsPerHouse() all houses are open")
{
    City_Grid city = City_Grid(10);
    CityState_Simple cityState{&city};

    // expected
    std::vector<int> expected{};
    for (int ii=0; ii<100; ++ii)
    {
        expected.push_back(ii);
    }

    // actual
    std::vector<int> actual{};
    std::unordered_set<const House*> actualHousesInRange = 
        cityState.getOpenHousesWithinRange(0, 9, 0, 9);
    for (const House* h : actualHousesInRange)
    {
        actual.push_back(h->getAddress());
    }

    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

    REQUIRE(expected == actual);
}

TEST_CASE("empty city - getResidentsPerHouse()")
{
    City_Grid city = City_Grid(10);
    CityState_Simple cityState{&city};

    //expected is empty set.
    std::unordered_map<const House*, Resident*> expected{};
    //const House* h = new House(12);
    //Resident* r = new Resident_UsingFunction(12, 1, 2.2, 1.0, make_unique<HappinessFunc_Flat>(22.3, 44), "Flat");
    //expected.insert({h,  r});


    std::unordered_map<const House*, Resident*> actual = cityState.getResidentsPerHouse();

    REQUIRE(expected == actual);
}

TEST_CASE("empty city - getHousePerResident()")
{
    City_Grid city = City_Grid(10);
    CityState_Simple cityState{&city};

    // expected is nullptr
    const House* expectedHouse = nullptr;

    Resident* r = new Resident_UsingFunction(
        12,
        1,
        2.2,
        1.0,
        make_unique<HappinessFunc_Flat>(22.3, 44),
        "Flat");

    REQUIRE(expectedHouse == cityState.getHousePerResident(r));
}

TEST_CASE("empty city - getResidentPerHouse()")
{
    City_Grid city = City_Grid(10);
    std::vector<const House*> houses = city.getHouses();
    CityState_Simple cityState{&city};

    // expectedResident is nullptr
    const Resident* expectedResident = nullptr;

    REQUIRE(expectedResident == cityState.getResidentPerHouse(houses[0]));
}

TEST_CASE("city with 10 residents at y = 5 - getOpenHousesWithinRange() limited range")
{
    City_Grid city = City_Grid(10);
    std::vector<const House*> houses = city.getHouses();

    CityState_Simple cityState{&city};

    std::vector<Resident*> residents{};
    for (int ii=0; ii<10; ++ii)
    {
        residents.push_back(new Resident_UsingFunction(
        ii,
        1,
        2.2,
        1.0,
        make_unique<HappinessFunc_Flat>(22.3, 44),
        "Flat"));
    }

    for (int ii=0; ii<10; ++ii)
    {
        cityState.moveIn(residents[ii], houses[10*5 + ii]);
    }

    // expected
    std::vector<int> expectedHouses{};
    for (int ii=0; ii<100; ++ii)
    {
        if ( (ii >= 35 && ii <= 39) || 
             (ii >= 45 && ii <= 49) ||
             (ii >= 65 && ii <= 69)
           ) 
        {
            expectedHouses.push_back(ii);
        }
    }

    // actualHouses
    std::vector<int> actualHouses{};
    std::unordered_set<const House*> actualHousesInRange = 
        cityState.getOpenHousesWithinRange(5, 9, 3, 6);
    for (const House* h : actualHousesInRange)
    {
        actualHouses.push_back(h->getAddress());
    }

    std::sort(actualHouses.begin(), actualHouses.end());

    REQUIRE(expectedHouses == actualHouses);
}

TEST_CASE("city with 10 residents at y = 5 - getOpenHousesWithinRange() entire city as range")
{
    City_Grid city = City_Grid(10);
    std::vector<const House*> houses = city.getHouses();

    CityState_Simple cityState{&city};

    std::vector<Resident*> residents{};
    for (int ii=0; ii<10; ++ii)
    {
        residents.push_back(new Resident_UsingFunction(
        ii,
        1,
        2.2,
        1.0,
        make_unique<HappinessFunc_Flat>(22.3, 44),
        "Flat"));
    }

    for (int ii=0; ii<10; ++ii)
    {
        cityState.moveIn(residents[ii], houses[10*5 + ii]);
    }

    // expected
    std::vector<int> expectedHouses{};
    for (int ii=0; ii<100; ++ii)
    {
        if (ii < 50 || ii > 59)
        {
            expectedHouses.push_back(ii);
        }
    }

    // actualHouses
    std::vector<int> actualHouses{};
    std::unordered_set<const House*> actualHousesInRange = 
        cityState.getOpenHousesWithinRange(0, 9, 0, 9);
    for (const House* h : actualHousesInRange)
    {
        actualHouses.push_back(h->getAddress());
    }

    std::sort(actualHouses.begin(), actualHouses.end());

    REQUIRE(expectedHouses == actualHouses);
}

TEST_CASE("move In and move Out")
{
    City_Grid city = City_Grid(10);
    std::vector<const House*> houses = city.getHouses();

    CityState_Simple cityState{&city};

    std::vector<Resident*> residents{};
    for (int ii=0; ii<10; ++ii)
    {
        residents.push_back(new Resident_UsingFunction(
        ii,
        1,
        2.2,
        1.0,
        make_unique<HappinessFunc_Flat>(22.3, 44),
        "Flat"));
    }

    // Move in row of residents at y == 10 and then move residents at x=0 through x=4 out.
        for (int ii=0; ii<10; ++ii)
        {
            cityState.moveIn(residents[ii], houses[10*5 + ii]);
        }

        for (int ii=0; ii<5; ++ii)
        {
            cityState.moveOut(residents[ii]);
        }

        // expected
        std::vector<int> expectedHouses{};
        for (int ii=0; ii<100; ++ii)
        {
            if ( (ii >= 30 && ii <= 39) || 
                (ii >= 40 && ii <= 49) ||
                (ii >= 50 && ii <= 54) ||
                (ii >= 60 && ii <= 69)
            ) 
            {
                expectedHouses.push_back(ii);
            }
        }

        // actualHouses
        std::vector<int> actualHouses{};
        std::unordered_set<const House*> actualHousesInRange = 
            cityState.getOpenHousesWithinRange(0, 9, 3, 6);
        for (const House* h : actualHousesInRange)
        {
            actualHouses.push_back(h->getAddress());
        }

        std::sort(actualHouses.begin(), actualHouses.end());

        REQUIRE(expectedHouses == actualHouses);

    // Move one resident back in

        cityState.moveIn(residents[0], houses[40]);

        //expected
        expectedHouses.erase(expectedHouses.begin() + 10);

        // actual
        std::vector<int> actualHousesB{};
        std::unordered_set<const House*>actualHousesInRangeB = cityState.getOpenHousesWithinRange(0, 9, 3, 6);
        for (const House* h : actualHousesInRangeB)
        {
            actualHousesB.push_back(h->getAddress());
        }

        std::sort(actualHousesB.begin(), actualHousesB.end());

        REQUIRE(expectedHouses == actualHousesB);

    // check getResidentsPerHouse()

        // expected
        std::unordered_map<const House*, Resident*> expectedResPerHouse{};
        for (int ii=5; ii<10; ++ii)
        {
            expectedResPerHouse.insert({houses[10*5 + ii], residents[ii]});
        }
        expectedResPerHouse.insert({houses[40], residents[0]});

        REQUIRE(expectedResPerHouse == cityState.getResidentsPerHouse());

    // check getHousePerResident()

        REQUIRE(nullptr == cityState.getHousePerResident(residents[2]));
        REQUIRE(houses[40] == cityState.getHousePerResident(residents[0]));
        REQUIRE(houses[59] == cityState.getHousePerResident(residents[9]));

    // check getResidentPerHouse()
        REQUIRE(nullptr == cityState.getResidentPerHouse(houses[51]));
        REQUIRE(residents[0] == cityState.getResidentPerHouse(houses[40]));
        REQUIRE(residents[9] == cityState.getResidentPerHouse(houses[59]));
}

TEST_CASE("moveInAndOutOfHouse()")
{
    City_Grid city = City_Grid(10);
    std::vector<const House*> houses = city.getHouses();

    CityState_Simple cityState{&city};

    std::vector<Resident*> residents{};
    for (int ii=0; ii<10; ++ii)
    {
        residents.push_back(new Resident_UsingFunction(
        ii,
        1,
        2.2,
        1.0,
        make_unique<HappinessFunc_Flat>(22.3, 44),
        "Flat"));
    }

    // Move in row of residents at y == 10 and then move residents at x=0 through x=4 out.
        for (int ii=0; ii<10; ++ii)
        {
            cityState.moveIn(residents[ii], houses[10*5 + ii]);
        }

    // Move residents 0 through 4 to next row (row y=6), at x equals 5 through 9
        for (int ii=0; ii<5; ++ii)
        {
            cityState.moveInAndOutOfHouse(residents[ii], houses[65 + ii]);
        }

        std::unordered_set<const House*> expectedOpenHouses{};
        for (int ii=0; ii<5; ++ii)
        {
            expectedOpenHouses.insert(houses[35 + ii]);
            expectedOpenHouses.insert(houses[45 + ii]);
            expectedOpenHouses.insert(houses[75 + ii]);
        }

        std::unordered_set<const House*> actual = 
            cityState.getOpenHousesWithinRange(5, 9, 3, 7);
        
        REQUIRE(expectedOpenHouses == actual);

      
    // check getResidentsPerHouse()

        // expected
        std::unordered_map<const House*, Resident*> expectedResPerHouse{};
        for (int ii=0; ii<5; ++ii)
        {
            expectedResPerHouse.insert({houses[55 + ii], residents[5 + ii]});
            expectedResPerHouse.insert({houses[65 + ii], residents[ii]});
        }

        std::unordered_map<const House*, Resident*> actualResPerHouse =
            cityState.getResidentsPerHouse();

        REQUIRE(expectedResPerHouse == cityState.getResidentsPerHouse());

    // check getHousePerResident()

        REQUIRE(houses[65] == cityState.getHousePerResident(residents[0]));
        REQUIRE(houses[59] == cityState.getHousePerResident(residents[9]));

    // check getResidentPerHouse()
        REQUIRE(residents[6] == cityState.getResidentPerHouse(houses[56]));
        REQUIRE(residents[1] == cityState.getResidentPerHouse(houses[66]));
}*/



