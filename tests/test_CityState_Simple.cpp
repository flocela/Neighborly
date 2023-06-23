#include "catch.hpp"

#include "../src/CityState_Simple.h"
#include "../src/HappinessFunc_Flat.h"
#include "../src/Resident_UsingFunction.h"
#include "../src/City_Grid.h"

using namespace std;

vector<int> getOpenAddressesWithinRange(
    const CityState_Simple cityState,
    int centerX,
    int centerY,
    double allowableDist
)
{
    vector<const House*> houses =
        cityState.getOpenHousesWithinRange(centerX, centerY, allowableDist);
    
    vector<int> addresses(houses.size());
    for (int ii=0; ii< houses.size(); ++ii)
    {
        addresses[ii] = houses[ii]->getAddress();
    }
    sort(addresses.begin(), addresses.end());
    return addresses;
}

// returns pointers to Residents, which need to be deleted.
vector<Resident*> createResidents (int numOfResidents)
{
    vector<Resident*> residents{};
    for (int ii=0; ii<numOfResidents; ++ii)
    {
        residents.push_back(new Resident_UsingFunction(
        ii,
        1,
        2.2,
        1.0,
        make_unique<HappinessFunc_Flat>(22.3, 44)));
    }
    return residents;
}

vector<int> createAddresses(
    int width,
    int centerX,
    int centerY,
    double allowableDist,
    unordered_set<int> excludeAddresses)
{
    vector<int> addresses{};
    int centerHouseAddress = centerY * width + centerX;

    for (int y = 0; y<=allowableDist; ++y)
    {
        int x = 0;
        int diffX = allowableDist - x;
        int diffY = allowableDist - y;
        int realDist = (diffX*diffX) + (diffY*diffY);
        while ((x <= allowableDist) && (realDist > (allowableDist *allowableDist)))
        {   
            ++x;
            diffX = allowableDist - x;
            diffY = allowableDist - y;
            realDist = (diffX*diffX) + (diffY*diffY);
        }
        int ltX = max(centerX - allowableDist + x, 0.0);
        int rtX = min(centerX + allowableDist - x, (double)width -1);
        int topY = centerY - allowableDist + y;
        int botY = centerY + allowableDist - y;
        
        for ( int ii=ltX; ii<=rtX; ++ii)
        {
            if (topY >= 0)
            {
                if (excludeAddresses.find(topY * width + ii) == excludeAddresses.end())
                {
                    addresses.push_back(topY*width + ii);
                }    
            }
            if (botY != topY && botY <= width-1)
            {
                if (excludeAddresses.find(botY * width + ii) == excludeAddresses.end())
                {
                    addresses.push_back(botY*width + ii);
                }
            }
        }
    }

    sort(addresses.begin(), addresses.end());
    return addresses;
}

TEST_CASE("empty city - getOpenHousesWithinRange() allowableDist=15")
{
    int width = 100;
    int centerX = 4;
    int centerY = 5;
    double allowableDist = 15; 

    City_Grid city = City_Grid(width);
    CityState_Simple cityState{&city};

    // expected
    vector<int> expected = 
        createAddresses(100, centerX, centerY, allowableDist,unordered_set<int>{});
    
    // actual
    vector<int> actual =
        getOpenAddressesWithinRange(cityState, centerX, centerY, allowableDist);

    REQUIRE(expected == actual);
}

// allowable distance is larger than the width of the city.
TEST_CASE("empty city - getOpenHouses() allowableDist encompasses every house")
{
    City_Grid city = City_Grid(50);
    CityState_Simple cityState{&city};

    // expected
    vector<int> expected{};
    for (int ii=0; ii<2500; ++ii)
    {
        expected.push_back(ii);
    }

    // actual
    vector<int> actual = getOpenAddressesWithinRange(cityState, 25, 25, 200);

    REQUIRE(expected == actual);
}

// empty city, there are no residents.
TEST_CASE("empty city - getResidentsPerHouse()")
{
    City_Grid city = City_Grid(10);
    CityState_Simple cityState{&city};

    //expected is empty set.
    unordered_map<const House*, Resident*> expected{};
    unordered_map<const House*, Resident*> actual = cityState.getResidentsPerHouse();

    REQUIRE(expected == actual);
}

// resident doesn't have a house in the city. So nullptr is returned for getHousePerResident()
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
        make_unique<HappinessFunc_Flat>(22.3, 44));

    REQUIRE(expectedHouse == cityState.getHousePerResident(r));
}

// there are no residents. So nullptr is returned for getResidentPerHouse()
TEST_CASE("empty city - getResidentPerHouse()")
{
    City_Grid city = City_Grid(10);
    vector<const House*> houses = city.getHouses();
    CityState_Simple cityState{&city};

    // expectedResident is nullptr
    const Resident* expectedResident = nullptr;

    REQUIRE(expectedResident == cityState.getResidentPerHouse(houses[0]));
}

// At y=5 and y=15, there are 10 residents, from x = 0 through 9.
TEST_CASE("city with 10 residents at y = 5 and y = 15 - getOpenHousesWithinRange() limited range")
{
    int width = 100;
    City_Grid city = City_Grid(width);
    vector<const House*> houses = city.getHouses();

    int centerX = 4;
    int centerY = 5;
    int centerHouseAddress = centerY * width + centerX;
    double allowableDist = 15;

    // Expected
    // all the houses within 15 units from centerX and centerY except those houses
    // that have residents in rows y=5 and y=15.
    unordered_set<int> occupiedHouses = {
        500, 501, 502, 503, 504, 505, 506, 507, 508, 509,
        1500, 1501, 1502, 1503, 1504, 1505, 1506, 1507, 1508, 1509
    };

    vector<int> expected = createAddresses(
        100,
        centerX,
        centerY,
        allowableDist,
        occupiedHouses
    );

    // Actual
    CityState_Simple cityState{&city};

    vector<Resident*> residents = createResidents(20);

    int curResId = 0;
    int y = 5;
    for (int ii=0; ii<10; ++ii)
    {
        cityState.moveIn(residents[curResId], houses[width*y + ii]);
        ++curResId;
    }

    y = 15;
    for (int ii=0; ii<10; ++ii)
    {
        cityState.moveIn(residents[curResId], houses[width*y + ii]);
        ++curResId;
    }

    vector<int> actual = getOpenAddressesWithinRange(
        cityState,
        centerX,
        centerY,
        allowableDist);

    REQUIRE(expected == actual);
    
    for (auto p : residents) 
    {
        delete p;
    }
}

TEST_CASE("move In and move Out")
{
    int width = 100;
    // center house and allowable distance used later in getOpenHousesWithRange() method.
    int centerX = 4;
    int centerY = 5;
    int centerHouseAddress = centerY * width + centerX;
    double allowableDist = 15;

    City_Grid city = City_Grid(width);
    CityState_Simple cityState{&city};

    // houses vector used later when moving residents into houses, and testing
    // getResidentPerHouse() and getHousePerResident() methods.
    vector<const House*> houses = city.getHouses();

    vector<Resident*> residents = createResidents(10);

    // moving residents in and out of row ten.
    int y = 10;

    // Move in ten residents at row y == 10 and then move residents at x=0 through x=4 out.
        for (int ii=0; ii<10; ++ii)
        {
            cityState.moveIn(residents[ii], houses[y * width + ii]);
        }

        for (int ii=0; ii<5; ++ii)
        {
            cityState.moveOut(residents[ii]);
        }

        // expected
        // exclude width * y + ii addresses, where ii is from 5 through 9.
        unordered_set<int> occupiedHouses = {1005, 1006, 1007, 1008, 1009};
        vector<int> expected = 
            createAddresses(width, centerX, centerY, allowableDist, occupiedHouses);

        // actual is 
        vector<int> actual = getOpenAddressesWithinRange(
            cityState,
            centerX,
            centerY,
            allowableDist);

        REQUIRE(expected == actual);

    // Move one resident back in

        cityState.moveIn(residents[0], houses[y*width]);

        //expected
        unordered_set<int> exclude =  {1000, 1005, 1006, 1007, 1008, 1009};
        expected = createAddresses(width, centerX, centerY, allowableDist, exclude);

        // actual
        actual = getOpenAddressesWithinRange(cityState, centerX, centerY, allowableDist);

        REQUIRE(expected == actual);

    // check getResidentsPerHouse()

        // expected
        unordered_map<int, Resident*> expectedResPerAddress{};
        expectedResPerAddress.insert({y*width, residents[0]});
        for (int ii=5; ii<10; ++ii)
        {
            expectedResPerAddress.insert({y*width + ii, residents[ii]});
        }

        // actual
        unordered_map<int, Resident*> actualResPerAddress{};
        unordered_map<const House*, Resident*> actualResPerHouse =
            cityState.getResidentsPerHouse();
        for (auto p : actualResPerHouse)
        {
            actualResPerAddress.insert({p.first->getAddress(), p.second});
        }
        REQUIRE(expectedResPerAddress == actualResPerAddress);

    // check getHousePerResident()

        REQUIRE(nullptr == cityState.getHousePerResident(residents[2]));
        REQUIRE(width*y == cityState.getHousePerResident(residents[0])->getAddress());
        REQUIRE(width*y + 9 == cityState.getHousePerResident(residents[9])->getAddress());

    // check getResidentPerHouse()
        const House* fifty = nullptr;
        const House* fiveHundred = nullptr;
        const House* fiveHundredAndNine = nullptr;
        for ( int ii=0; ii< houses.size(); ++ii)
        {
            if (houses[ii]->getAddress() == 50)
            {
                fifty = houses[ii];
            }
            else if (houses[ii]->getAddress() == 1000)
            {
                fiveHundred = houses[ii];
            }
            else if (houses[ii]->getAddress() == 1009)
            {
                fiveHundredAndNine = houses[ii];
            }
        }
        REQUIRE(nullptr == cityState.getResidentPerHouse(fifty));
        REQUIRE(residents[0] == cityState.getResidentPerHouse(fiveHundred));
        REQUIRE(residents[9] == cityState.getResidentPerHouse(fiveHundredAndNine));

        for (auto p : residents) 
        {
        delete p;
        }
}