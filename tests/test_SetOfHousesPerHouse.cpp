#include "catch.hpp"

#include "../src/SetOfHousesPerHouse.h"

using namespace std;

TEST_CASE("SetOfHousesPerHouse:: check insert() and containsKey()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    House house5{5};
    House house6{6};
    House house7{7};
    House house8{8};

    SetOfHousesPerHouse setOfHousesPerHouse{};

    setOfHousesPerHouse.insert(&house1, &house2);
    setOfHousesPerHouse.insert(&house1, &house3);
    setOfHousesPerHouse.insert(&house1, &house4);

    setOfHousesPerHouse.insert(&house5, &house6);
    setOfHousesPerHouse.insert(&house5, &house7);
    setOfHousesPerHouse.insert(&house5, &house8);

    REQUIRE(false == setOfHousesPerHouse.containsKey(&house2));
    REQUIRE(true == setOfHousesPerHouse.containsKey(&house1));
    REQUIRE(true == setOfHousesPerHouse.containsKey(&house5));
    
}

TEST_CASE("SetOfHousesPerHouse:: check at()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    House house5{5};
    House house6{6};
    House house7{7};
    House house8{8};

    SetOfHousesPerHouse setOfHousesPerHouse{};

    setOfHousesPerHouse.insert(&house1, &house2);
    setOfHousesPerHouse.insert(&house1, &house3);
    setOfHousesPerHouse.insert(&house1, &house4);

    setOfHousesPerHouse.insert(&house5, &house6);
    setOfHousesPerHouse.insert(&house5, &house7);
    setOfHousesPerHouse.insert(&house5, &house8);
    setOfHousesPerHouse.insert(&house5, &house1);

    unordered_set<int> secondSetIds = {6, 7, 8, 1};

    unordered_set<const House*> secondSet = setOfHousesPerHouse.at(&house5);

    for (auto houseFromSecondSet : secondSet)
    {
        REQUIRE(secondSetIds.find(houseFromSecondSet->getAddress()) != secondSetIds.end());
        secondSetIds.erase(houseFromSecondSet->getAddress());
    }

    REQUIRE(secondSetIds.size() == 0);
    
}

TEST_CASE("SetOfHousesPerHouse:: check begin() and end()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    House house5{5};
    House house6{6};
    House house7{7};
    House house8{8};

    SetOfHousesPerHouse setOfHousesPerHouse{};

    setOfHousesPerHouse.insert(&house1, &house2);
    setOfHousesPerHouse.insert(&house1, &house3);
    setOfHousesPerHouse.insert(&house1, &house4);

    setOfHousesPerHouse.insert(&house5, &house6);
    setOfHousesPerHouse.insert(&house5, &house7);
    setOfHousesPerHouse.insert(&house5, &house8);
    setOfHousesPerHouse.insert(&house5, &house1);

    unordered_set<int> keyHouses = {1, 5};

    auto it = setOfHousesPerHouse.begin();
    while (it != setOfHousesPerHouse.end())
    {
        REQUIRE(keyHouses.find(it->first->getAddress()) != keyHouses.end());
        keyHouses.erase(it->first->getAddress());
        ++it;
    }

    REQUIRE(keyHouses.size() == 0);
    
}


TEST_CASE("SetOfHousesPerHouse:: check cbegin() and cend()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    House house5{5};
    House house6{6};
    House house7{7};
    House house8{8};

    SetOfHousesPerHouse setOfHousesPerHouse{};

    setOfHousesPerHouse.insert(&house1, &house2);
    setOfHousesPerHouse.insert(&house1, &house3);
    setOfHousesPerHouse.insert(&house1, &house4);

    setOfHousesPerHouse.insert(&house5, &house6);
    setOfHousesPerHouse.insert(&house5, &house7);
    setOfHousesPerHouse.insert(&house5, &house8);
    setOfHousesPerHouse.insert(&house5, &house1);

    unordered_set<int> keyHouses = {1, 5};

    auto it = setOfHousesPerHouse.cbegin();
    while (it != setOfHousesPerHouse.cend())
    {
        REQUIRE(keyHouses.find(it->first->getAddress()) != keyHouses.end());
        keyHouses.erase(it->first->getAddress());
        ++it;
    }

    REQUIRE(keyHouses.size() == 0);
    
}