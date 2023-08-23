#include "catch.hpp"

#include "../src/HappinessFunc_Flat.h"
#include "../src/ResPerHouse.h"
#include "../src/Resident_Customizable.h"

using namespace std;

TEST_CASE("ResPerHouse:: check insert() and contains()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    Resident_Customizable res1{1, 1, .1, .1, make_unique<HappinessFunc_Flat>(.1, .1)};
    Resident_Customizable res2{2, 2, .2, .2, make_unique<HappinessFunc_Flat>(.2, .2)};
    Resident_Customizable res3{3, 3, .3, .3, make_unique<HappinessFunc_Flat>(.3, .3)};
    Resident_Customizable res4{4, 4, .4, .4, make_unique<HappinessFunc_Flat>(.4, .4)};

    ResPerHouse rph{};

    rph.insert({&house1, &res1});
    rph.insert({&house2, &res2});
    rph.insert({&house3, &res3});

    REQUIRE(true == rph.contains(&house1));
    REQUIRE(false == rph.contains(&house4));
    
}

TEST_CASE("ResPerHouse:: check insert() and at()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    Resident_Customizable res1{1, 1, .1, .1, make_unique<HappinessFunc_Flat>(.1, .1)};
    Resident_Customizable res2{2, 2, .2, .2, make_unique<HappinessFunc_Flat>(.2, .2)};
    Resident_Customizable res3{3, 3, .3, .3, make_unique<HappinessFunc_Flat>(.3, .3)};
    Resident_Customizable res4{4, 4, .4, .4, make_unique<HappinessFunc_Flat>(.4, .4)};

    ResPerHouse rph{};

    rph.insert({&house1, &res1});
    rph.insert({&house2, &res2});
    rph.insert({&house3, &res3});

    REQUIRE(&res1 == rph.at(&house1));
    REQUIRE_THROWS(rph.at(&house4));
}

TEST_CASE("ResPerHouse:: check cbegin() and cend()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    Resident_Customizable res1{1, 1, .1, .1, make_unique<HappinessFunc_Flat>(.1, .1)};
    Resident_Customizable res2{2, 2, .2, .2, make_unique<HappinessFunc_Flat>(.2, .2)};
    Resident_Customizable res3{3, 3, .3, .3, make_unique<HappinessFunc_Flat>(.3, .3)};
    Resident_Customizable res4{4, 4, .4, .4, make_unique<HappinessFunc_Flat>(.4, .4)};

    ResPerHouse rph{};

    rph.insert({&house1, &res1});
    rph.insert({&house2, &res2});
    rph.insert({&house3, &res3});
    rph.insert({&house4, &res4});

    unordered_set<int> houseAddresses = {1, 2, 3, 4};
    auto it = rph.cbegin();
    while (it != rph.cend())
    {
        REQUIRE(it->first->getAddress() == it->second->getID());
        houseAddresses.erase(it->first->getAddress());
        ++it;
    }

    REQUIRE(houseAddresses.size() == 0);

}

TEST_CASE("ResPerHouse:: check begin() and end()")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    Resident_Customizable res1{1, 1, .1, .1, make_unique<HappinessFunc_Flat>(.1, .1)};
    Resident_Customizable res2{2, 2, .2, .2, make_unique<HappinessFunc_Flat>(.2, .2)};
    Resident_Customizable res3{3, 3, .3, .3, make_unique<HappinessFunc_Flat>(.3, .3)};
    Resident_Customizable res4{4, 4, .4, .4, make_unique<HappinessFunc_Flat>(.4, .4)};

    ResPerHouse rph{};

    rph.insert({&house1, &res1});
    rph.insert({&house2, &res2});
    rph.insert({&house3, &res3});
    rph.insert({&house4, &res4});

    unordered_set<int> houseAddresses = {1, 2, 3, 4};
    auto it = rph.begin();
    while (it != rph.end())
    {
        REQUIRE(it->first->getAddress() == it->second->getID());
        houseAddresses.erase(it->first->getAddress());
        ++it;
    }

    REQUIRE(houseAddresses.size() == 0);

}

TEST_CASE("ResPerHouse:: check == operator")
{
    House house1{1};
    House house2{2};
    House house3{3};
    House house4{4};

    Resident_Customizable res1{1, 1, .1, .1, make_unique<HappinessFunc_Flat>(.1, .1)};
    Resident_Customizable res2{2, 2, .2, .2, make_unique<HappinessFunc_Flat>(.2, .2)};
    Resident_Customizable res3{3, 3, .3, .3, make_unique<HappinessFunc_Flat>(.3, .3)};
    Resident_Customizable res4{4, 4, .4, .4, make_unique<HappinessFunc_Flat>(.4, .4)};

    ResPerHouse rphA{};

    rphA.insert({&house1, &res1});
    rphA.insert({&house2, &res2});
    rphA.insert({&house3, &res3});
    //rph.insert({&house4, &res4});

    ResPerHouse rphB{};

    rphB.insert({&house1, &res1});
    rphB.insert({&house2, &res2});
    rphB.insert({&house3, &res3});
    rphB.insert({&house4, &res4});

    ResPerHouse rphC{};

    rphC.insert({&house1, &res1});
    rphC.insert({&house2, &res2});
    rphC.insert({&house3, &res3});
    rphC.insert({&house4, &res4});

    REQUIRE(rphA == rphA);
    REQUIRE(false == (rphA == rphB));
    REQUIRE(true == (rphB == rphC));
}