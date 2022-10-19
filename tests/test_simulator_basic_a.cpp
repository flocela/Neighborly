#include "catch.hpp"
#include "../src/Simulator_Basic_A.h"
#include "../src/City_Grid.h"
#include "../src/Resident_Flat.h"
#include "../src/Resident_StepDown.h"
#include "../src/Color.h"
#include "../src/Coordinate.h"

using std::set;
using std::vector;
using std::unique_ptr;

template<typename T>
std::set<T*> getSetOfPointers (vector<unique_ptr<T>>& ts)
{
    std::set<T*> pointers = {};
    for (auto& t : ts)
    {
        pointers.insert(t.get());
    }
    return pointers;
}

template<typename K, typename V>
std::unordered_map<V, K> reverseMap (std::unordered_map<K, V> const& orig)
{
    std::unordered_map<V, K> returnedMap;
    for (auto const& kv : orig)
    {
        returnedMap.insert(std::pair<V, K>(kv.second, kv.first));
    }
    return returnedMap;
} 

TEST_CASE("four runs happy resident stays unhappy resident moves")
{
    unique_ptr<City> city = std::make_unique<City_Grid>(20);
    vector<unique_ptr<Resident>> residents;

    unique_ptr<Resident> happy = std::make_unique<Resident_Flat>(
        1,
        3,
        5,
        1.0, // happiness goal
        1.0  // happiness value
    );

    unique_ptr<Resident> unhappy = std::make_unique<Resident_Flat>(
        2,
        1,
        5,
        1.0, // happiness goal
        0.5  // happiness value
    );
    // Need pointers for later use.
    Resident* happyPtr = happy.get();
    Resident* unhappyPtr = unhappy.get();
    residents.push_back(std::move(happy));
    residents.push_back(std::move(unhappy));

    Simulator_Basic_A simulator{city.get(), getSetOfPointers(residents)};
    std::unordered_map<const House*, Resident*> houseToResMap = simulator.simulate();
    std::unordered_map<Resident*, const House*> resToHouseMap = reverseMap(houseToResMap);
   
    Coordinate currHappyCoord = city->getCoordinate(resToHouseMap[happyPtr]->getAddress());
    Coordinate currUnhappyCoord = city->getCoordinate(resToHouseMap[unhappyPtr]->getAddress());

    for (int ii=0; ii<4; ++ii)
    {
        Coordinate pastHappyCoord = currHappyCoord;
        Coordinate pastUnhappyCoord = currUnhappyCoord;
        houseToResMap = simulator.simulate();
        resToHouseMap = reverseMap(houseToResMap);
        Coordinate currHappyCoord = city->getCoordinate(resToHouseMap[happyPtr]->getAddress());
        Coordinate currUnhappyCoord = city->getCoordinate(resToHouseMap[unhappyPtr]->getAddress());
        REQUIRE(pastHappyCoord == currHappyCoord);
        REQUIRE(pastUnhappyCoord != currUnhappyCoord);
    }
}

TEST_CASE ("2 runs with many residents whose allowable movement is the whole city")
{   
    vector<unique_ptr<Resident>> residents;
    set<Resident*> resPtrs;
    for (int ii=0; ii<=6; ++ii)
    {
        // Blue residents become unhappy when diversity is 0.5 or greater.
        residents.push_back(std::make_unique<Resident_StepDown>(
            ii,          // id
            1, // color
            5.0,         // movement
            0.5,         // happiness goal
            1.0,
            0.75,        // happiness at diversity of zero
            0.25,        // happiness at diversity of one
            0.5          // diversity where drop happens
        ));
        resPtrs.insert(residents[ii].get());
    }

    for (int jj=7; jj <= 13; ++jj)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            jj,         // id
            3, // color
            5.0,        // movement
            0.5,        // happiness goal
            1.0,
            0.75,       // happiness at diversity of zero
            0.25,       // happiness at diversity of one
            0.5
        ));
        resPtrs.insert(residents[jj].get());
    }

    int cityWidth = 5;
    City_Grid city{cityWidth};
    std::vector<const House*> houses = city.getHouses();
    Simulator_Basic_A sim{&city, resPtrs};

    // Simulation zero. (first simulation)
    // separate happy and unhappy residents into two maps.
    std::unordered_map<const House*, Resident*> housToResMapSimZero = sim.simulate();

    std::map<int, int> happyResIDToAddressMapSimZero;
    std::map<int, int> unhappyResIDToAddressMapSimZero;
    for (auto h2R : housToResMapSimZero)
    {
        const House* house = h2R.first;
        Resident* res = h2R.second;
        if (res->getHappiness() < res->getHappinessGoal())
        {   
            unhappyResIDToAddressMapSimZero.insert(
                std::pair<int, int>(res->getID(), house->getAddress())
            );
        }
        else
        {   
            happyResIDToAddressMapSimZero.insert(
                std::pair<int, int>(res->getID(), house->getAddress())
            );
        }
    }

    // Simulation one.
    // Check previously unhappy residents moved. Previously happy didn't move.
    std::unordered_map<const House*, Resident*> housToResMapSimOne = sim.simulate();

    std::map<int, int> resIDToAddressSimOne;
    for (auto h2R: housToResMapSimOne)
    {
        resIDToAddressSimOne.insert(
            std::pair<int, int>(h2R.second->getID(), h2R.first->getAddress())
        );
    }

    // Test originally happy residents stayed in the same house.
    for (auto oneR2H :  happyResIDToAddressMapSimZero)
    {
        REQUIRE(oneR2H.second == resIDToAddressSimOne[oneR2H.first]);
    }

    // Test originally unhappy residents moved to different house.
    for (auto oneR2H :  unhappyResIDToAddressMapSimZero)
    {
        REQUIRE(oneR2H.second != resIDToAddressSimOne[oneR2H.first]);
    }
}

TEST_CASE ("2 runs with many residents whose allowable movement is zero")
{   
    vector<unique_ptr<Resident>> residents;
    set<Resident*> resPtrs;
    for (int ii=0; ii<=6; ++ii)
    {
        // Blue residents become unhappy when diversity is 0.5 or greater.
        residents.push_back(std::make_unique<Resident_StepDown>(
            ii,          // id
            1, // color
            0.0,         // NO movement
            0.5,         // happiness goal
            1.0,
            0.75,        // happiness at diversity of zero
            0.25,        // happiness at diversity of one
            0.5          // diversity where drop happens
        ));
        resPtrs.insert(residents[ii].get());
    }

    for (int jj=7; jj <= 13; ++jj)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            jj,         // id
            3, // color
            0.0,        // NO movement
            0.5,        // happiness goal
            1.0,
            0.75,       // happiness at diversity of zero
            0.25,       // happiness at diversity of one
            0.5         // diversity where drop happens
        ));
        resPtrs.insert(residents[jj].get());
    }

    int cityWidth = 5;
    City_Grid city{cityWidth};
    std::vector<const House*> houses = city.getHouses();
    Simulator_Basic_A sim{&city, resPtrs};

    // Simulation zero. (first simulation)
    // separate happy and unhappy residents into two maps.
    std::unordered_map<const House*, Resident*> housToResMapSimZero = sim.simulate();

    std::map<int, int> happyResIDToAddressMapSimZero;
    std::map<int, int> unhappyResIDToAddressMapSimZero;
    for (auto h2R : housToResMapSimZero)
    {
        const House* house = h2R.first;
        Resident* res = h2R.second;
        if (res->getHappiness() < res->getHappinessGoal())
        {   
            unhappyResIDToAddressMapSimZero.insert(
                std::pair<int, int>(res->getID(), house->getAddress())
            );
        }
        else
        {   
            happyResIDToAddressMapSimZero.insert(
                std::pair<int, int>(res->getID(), house->getAddress())
            );
        }
    }

    // Simulation one.
    // Check previously happy and unhappy residents stayed in the same house.
    std::unordered_map<const House*, Resident*> housToResMapSimOne = sim.simulate();

    std::map<int, int> resIDToAddressSimOne;
    for (auto h2R: housToResMapSimOne)
    {
        resIDToAddressSimOne.insert(
            std::pair<int, int>(h2R.second->getID(), h2R.first->getAddress())
        );
    }

    // Test originally happy residents stayed in the same house.
    for (auto oneR2H :  happyResIDToAddressMapSimZero)
    {
        REQUIRE(oneR2H.second == resIDToAddressSimOne[oneR2H.first]);
    }

    // Test originally unhappy residents also stayed in the same house.
    for (auto oneR2H :  unhappyResIDToAddressMapSimZero)
    {
        REQUIRE(oneR2H.second == resIDToAddressSimOne[oneR2H.first]);
    }
}

TEST_CASE ("2 runs with many residents whose allowable movement is 2.0")
{   
    vector<unique_ptr<Resident>> residents;
    set<Resident*> resPtrs;
    for (int ii=0; ii<=6; ++ii)
    {
        // Blue residents become unhappy when diversity is 0.5 or greater.
        residents.push_back(std::make_unique<Resident_StepDown>(
            ii,          // id
            1, // color
            2.0,         // allowable movement
            0.5,         // happiness goal
            1.0,
            0.75,        // happiness at diversity of zero
            0.25,        // happiness at diversity of one
            0.5          // diversity where drop happens
        ));
        resPtrs.insert(residents[ii].get());
    }

    for (int jj=7; jj <= 13; ++jj)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            jj,         // id
            3, // color
            2.0,        // allowable movement
            0.5,        // happiness goal
            1.0,
            0.75,       // happiness at diversity of zero
            0.25,       // happiness at diversity of one
            0.5         // diversity where drop happens
        ));
        resPtrs.insert(residents[jj].get());
    }

    int cityWidth = 5;
    City_Grid city{cityWidth};
    std::vector<const House*> houses = city.getHouses();
    Simulator_Basic_A sim{&city, resPtrs};

    // Simulation zero. (first simulation)
    // Get unhappy residents into one map.
    std::unordered_map<const House*, Resident*> housToResMapSimZero = sim.simulate();

    std::unordered_map<int, int> unhappyResToHousMapSimZero;
    for (auto h2R : housToResMapSimZero)
    {
        const House* house = h2R.first;
        Resident* res = h2R.second;
        if (res->getHappiness() < res->getHappinessGoal())
        {   
            unhappyResToHousMapSimZero.insert(
                std::pair<int, int>(res->getID(), house->getAddress()
            ));
        }
    }

    // Simulation one.
    // Check previously unhappy residents only moved 2 units away from orig house.
    std::unordered_map<const House*, Resident*> housToResMapSimOne = sim.simulate();
    std::map<int, int> resToHouseMapSimOne;
    for (auto h2R : housToResMapSimOne)
    {
        resToHouseMapSimOne.insert(
            std::pair<int, int>(h2R.second->getID(),
            h2R.first->getAddress())
        );
    }

    // Test originally unhappy residents didn't move more than 2 units.
    for (auto r2HSimZero :  unhappyResToHousMapSimZero)
    {
        double distance = city.getDist(
            r2HSimZero.second,
            resToHouseMapSimOne[r2HSimZero.first]
        );
        REQUIRE(distance <= 2.0);
    }
}