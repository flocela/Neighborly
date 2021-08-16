#include "catch.hpp"
#include "../src/Resident_Flat.h"
#include "../src/Resident_StepDown.h"
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor01{1, Color::blue, 0.0, 0.0, 0.0 };

Resident_StepDown redNeighbor02{2, Color::red, 0.0, 0.25, 0.1, 0.0, 0.0};

Resident_StepDown redNeighbor03{3, Color::red, 0.0, 0.25, 0.1, 0.0, 0.0};
    
Resident_StepDown greenNeighbor04{4, Color::green, 0.0, 0.0, 0.1, 0.0, 0.0};

Resident_StepDown greenNeighbor05{5, Color::green, 0.0, 0.0, 0.1, 0.0, 0.0};

Resident_StepDown greenNeighbor06{6, Color::green, 0.0, 0.0, 0.1, 0.0, 0.0};

TEST_CASE("Resident_Flat Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(Resident_Flat(
            0,
            Color::green,
            0,
            1.2,
            0.0
        ), 
        Contains("HappinessGoal must be between 0.0 and 1.0 inclusive.") 
    );
}


TEST_CASE("Resident_Flat Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_Flat(
            0,
            Color::green,
            0.0,
            -0.1,
            0.0
        ), 
        Contains("HappinessGoal must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_Flat Ctor throws exception if happinessValue is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Flat(
            0, 
            Color::green,
            0.0,
            0.0,
            1.2
        ), 
        Contains("HappinessValue must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_Flat Ctor throws exception if happinessValue is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Flat(
            0, 
            Color::green,
            0.0,
            0.0,
            -.25
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}


TEST_CASE("getHappines() returns happinessValue")
{
    Resident_Flat blueResident {0, Color::blue, 0.0, 0.0, 0.25};
    std::set<Resident*> neighbors = { 
        &blueNeighbor01,
        &greenNeighbor04,
        &greenNeighbor05,
        &greenNeighbor06
    };
    REQUIRE(blueResident.calculateHappiness(neighbors, 4) == 0.25);
}

TEST_CASE("toStrBasic() ")
{
    Resident_Flat resident { 1,
                            Color::green,
                            1.0,
                            1.0,
                            0.25 };
    REQUIRE(resident.toStrBasic() == "Res_Flat(id, clr, mov, goal, hapV):"
        " (1, green, 1.000000, 1.000000, 0.250000)");
}