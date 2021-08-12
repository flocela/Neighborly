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
std::map<V, K> reverseMap (std::map<K, V> const& orig)
{
    std::map<V, K> returnedMap;
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
        Color::red,
        5,
        1.0, // happiness goal
        1.0  // happiness value
    );

    unique_ptr<Resident> unhappy = std::make_unique<Resident_Flat>(
        2,
        Color::blue,
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
    std::map<House*, Resident*> houseToResMap = simulator.simulate();
    std::map<Resident*, House*> resToHouseMap = reverseMap(houseToResMap);
   
    Coordinate currHappyCoord = city->getCoordinate(resToHouseMap[happyPtr]->_address);
    Coordinate currUnhappyCoord = city->getCoordinate(resToHouseMap[unhappyPtr]->_address);

    for (int ii=0; ii<4; ++ii)
    {
        Coordinate pastHappyCoord = currHappyCoord;
        Coordinate pastUnhappyCoord = currUnhappyCoord;
        houseToResMap = simulator.simulate();
        resToHouseMap = reverseMap(houseToResMap);
        Coordinate currHappyCoord = city->getCoordinate(resToHouseMap[happyPtr]->_address);
        Coordinate currUnhappyCoord = city->getCoordinate(resToHouseMap[unhappyPtr]->_address);
        REQUIRE(pastHappyCoord == currHappyCoord);
        REQUIRE(pastUnhappyCoord != currUnhappyCoord);
    }
}

TEST_CASE ("two runs with many residents")
{   
    vector<unique_ptr<Resident>> residents;
    set<Resident*> resPtrs;
    for (int ii=0; ii<=6; ++ii)
    {
        // Blue residents become unhappy when diversity is 
        residents.push_back(std::make_unique<Resident_StepDown>(
            ii,           // id
            Color::blue, // color
            0.0,         // movement
            0.5,        // happiness goal
            0.75,        // happiness at zero diversity
            0.25,        // happiness at one diversity
            0.5          // diversity where drop happens
        ));
        resPtrs.insert(residents[ii].get());
    }

    for (int jj=7; jj <= 13; ++jj)
    {
        residents.push_back(std::make_unique<Resident_StepDown>(
            jj,
            Color::red, 
            0.0,  
            0.5, 
            0.75, 
            0.25, 
            0.5
        ));
        resPtrs.insert(residents[jj].get());
    }

    int run = 1;
    int maxNumOfRuns = 10;
    int cityWidth = 5;
    std::string title = "title";
    City_Grid city{cityWidth};
    std::vector<House*> houses = city.getHouses();
    Simulator_Basic_A sim{&city, resPtrs};

    // first simulation.
    std::map<House*, Resident*> oneHouseToResidentMap = sim.simulate();

    std::map<int, int> oneHappyResidentIDToAddressMap;
    std::map<int, int> oneUnhappyResidentIDToAddressMap;
    for (auto h2R : oneHouseToResidentMap)
    {
        House* house = h2R.first;
        Resident* res = h2R.second;
        if (res->getHappiness() < res->getHappinessGoal())
        {   
            oneUnhappyResidentIDToAddressMap.insert(
                std::pair<int, int>(res->getID(), house->_address)
            );
        }
        else
        {   
            oneHappyResidentIDToAddressMap.insert(
                std::pair<int, int>(res->getID(), house->_address)
            );
        }
    }

    // second simulation.
    // Check previously unhappy residents moved. {reviously happy didn't move.
    std::map<House*, Resident*> twoHouseToResidentMap = sim.simulate();

    std::map<int, int> twoResIDToAddress;
    for (auto h2R: twoHouseToResidentMap)
    {
        twoResIDToAddress.insert(
            std::pair<int, int>(h2R.second->getID(), h2R.first->_address)
        );
    }

    for (auto oneR2H :  oneHappyResidentIDToAddressMap)
    {
        REQUIRE(oneR2H.second == twoResIDToAddress[oneR2H.first]);
    }

    for (auto oneR2H :  oneUnhappyResidentIDToAddressMap)
    {
        REQUIRE(oneR2H.second != twoResIDToAddress[oneR2H.first]);
    }
}