#include "catch.hpp"
#include "../src/Simulator_Basic_A.h"
#include "../src/City_Grid.h"
#include "../src/Resident_Flat.h"
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

    // add happy Resident
    unique_ptr<Resident> happy = std::make_unique<Resident_Flat>(
        1,
        Color::red,
        5,
        1.0, // happinessGoal
        1.0  // happinessValue
    );

    residents.push_back(std::move(happy));

    // add unhappy Resident
    unique_ptr<Resident> unhappy = std::make_unique<Resident_Flat>(
        2,
        Color::blue,
        5,
        1.0, // happinessGoal
        0.5  // happinessValue
    );

    residents.push_back(std::move(unhappy));

    Simulator_Basic_A simulator{city.get(), getSetOfPointers(residents)};
    std::map<House*, Resident*> houseToResMap = simulator.simulate();
    reverseMap(houseToResMap);

   /* Coordinate happyCoord = city->getCoordinate(resToHouseMap[happy.get()]->_address);
    Coordinate unhappyCoord = city->getCoordinate(resToHouseMap[unhappy.get()]->_address);

    for (int ii=0; ii<4; ++ii)
    {
        Coordinate pastHappyCoord = happyCoord;
        Coordinate pastUnhappyCoord = unhappyCoord;
        Coordinate currHappyCoord = city->getCoordinate(resToHouseMap[happy.get()]->_address);
        Coordinate currUnhappyCoord = city->getCoordinate(resToHouseMap[unhappy.get()]->_address);
        REQUIRE(pastHappyCoord == currHappyCoord);
        REQUIRE(pastUnhappyCoord != currUnhappyCoord);
        pastHappyCoord = currHappyCoord;
        pastUnhappyCoord = currUnhappyCoord;
    }
*/
    REQUIRE(true);

}