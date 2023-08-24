#include "catch.hpp"

#include "../src/HappinessFunc_Falling.h"
#include "../src/Resident_Customizable.h"

using namespace std;

TEST_CASE("Resident_Customizable:: check getLeastPossibleHappiness()")
{

    Resident_Customizable res1{1, 1, .1, .1, make_unique<HappinessFunc_Falling>(.5, .9, .1)};

    REQUIRE(.1 == res1.getLeastPossibleHappiness());
    REQUIRE(.9 == res1.getMaximumPossibleHappiness());
    
}

TEST_CASE("Resident_Customizable:: check Resident methods")
{

    Resident_Customizable res1{1, 2, 5, .7, make_unique<HappinessFunc_Falling>(.5, .9, .1)};

    Resident_Customizable n1{1, 1, 5, .7, make_unique<HappinessFunc_Falling>(.5, .9, .1)};
    Resident_Customizable n2{2, 1, 5, .7, make_unique<HappinessFunc_Falling>(.5, .9, .1)};
    Resident_Customizable n3{3, 2, 5, .7, make_unique<HappinessFunc_Falling>(.5, .9, .1)};
    Resident_Customizable n4{4, 2, 5, .7, make_unique<HappinessFunc_Falling>(.5, .9, .1)};
    unordered_set<const Resident*> neighbors{};
    neighbors.insert(&n1);
    neighbors.insert(&n2);
    neighbors.insert(&n3);
    neighbors.insert(&n4);

    REQUIRE(1 == res1.getID());
    REQUIRE(2 == res1.getGroupId());
    REQUIRE(5 == res1.getAllowedMovementDistance());
    REQUIRE(.7 == res1.getHappinessGoal());
    REQUIRE(.5 == res1.calculateHappiness(neighbors, 10));
    REQUIRE(0.0 == res1.getHappiness());
    res1.setHappiness(neighbors,10);
    REQUIRE(0.5 == res1.getHappiness());
}