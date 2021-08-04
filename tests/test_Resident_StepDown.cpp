#include "catch.hpp"
#include "../src/Resident_StepDown.h"
#include "../src/Resident_Flat.h"
#include <set>
using Catch::Matchers::Contains;

Resident_StepDown blueNeighbor1{
    2,
    Color::blue, // Only argument that matters.
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor2{
    2,
    Color::blue, // Only argument that matters.
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor3{
    2,
    Color::blue, // Only argument that matters.
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};
    
Resident_StepDown greenNeighbor1{
    2,
    Color::green, // Only argument that matters.
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown greenNeighbor2{
    2,
    Color::green, // Only argument that matters.
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown greenNeighbor3{
    2,
    Color::green, // Only argument that matters.
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};
    

TEST_CASE("Resident_StepDown Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0, // allowedMovementDistance
                          1.2, // happinessGoal
                          1.0, // happinessValueAtZeroDiversity
                          0.0, // diversityWhereDropHappens
                         0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );

}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          -0.25,
                          1.0,
                          0.0,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at zero is less tahn zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          -0.3,
                          0.0,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          1.2,
                          0.0,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at one is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          0.3,
                          -0.3,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          .5,
                          1.2,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if diverstiyWhereDropHappens is less than 0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          1.0,
                          0.0,
                          -1.0 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if diverstiyWhereDropHappens is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          1.0,
                          0.0,
                          1.1), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if"
" happinessValueAtZeroDiversity is smaller than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          .25,
                          .75,
                          0.5), Contains("happinessAtZeroDiversity must be"
                          " larger than happinessAtOneDiversity.") );
}

TEST_CASE("Resident_StepDown Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          .75,
                          .75,
                          0.5), Contains("happinessAtZeroDiversity must be"
                          " larger than happinessAtOneDiversity.") );
}


TEST_CASE("getHappines() returns lowered happinessValue at point where drop happens.")
{
    // Note diversity Ratio is 0.5. @diverstiyWhereDropHappens is 0.25.
    Resident_StepDown greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
        0.25   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &greenNeighbor1,
        &greenNeighbor2,
        &greenNeighbor3,
        &blueNeighbor1
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.25);
}

TEST_CASE("getHappines() returns higher happinessValue before diversity drop.")
{
    // Note diversity Ratio is 0.25. @diverstiyWhereDropHappens is 0.5.
    Resident_StepDown greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &blueNeighbor1,
        &greenNeighbor1,
        &greenNeighbor2,
        &greenNeighbor3
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.75);
}

TEST_CASE("getHappines() returns lower happinessValue afterDiversity drop.")
{
    // Note diversity Ratio is 0.25. @diverstiyWhereDropHappens is 0.25.
    Resident_StepDown greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &blueNeighbor1,
        &blueNeighbor2,
        &blueNeighbor3,
        &greenNeighbor1,
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.25);
}

TEST_CASE("ostream operator <<")
{
    Resident_StepDown greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };
    REQUIRE(greenResident.toStr() == "Res_StepDown(id, clr, mov, goal, hap0, hap1, drop): (1, green, 0.000000, 0.250000, 0.750000, 0.250000, 0.500000). Happiness is 0.000000");
}