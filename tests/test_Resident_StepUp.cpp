#include "catch.hpp"
#include "../src/Resident_StepUp.h"
using Catch::Matchers::Contains;


Resident_StepUp blNeighbor01{
    1,
    Color::blue, // Only argument that matters.
    0.0,  
    0.25, 
    0.25, 
    0.75, 
    0.5   
};

Resident_StepUp blNeighbor02{
    2,
    Color::blue, // Only argument that matters.
    0.0,  
    0.25, 
    0.25, 
    0.75, 
    0.5   
};

Resident_StepUp blNeighbor03{
    3,
    Color::blue, // Only argument that matters.
    0.0,  
    0.25, 
    0.25, 
    0.75, 
    0.5   
};
    
Resident_StepUp grNeighbor01{
    11,
    Color::green, // Only argument that matters.
    0.0,  
    0.25, 
    0.25, 
    0.75, 
    0.5   
};

Resident_StepUp grNeighbor02{
    12,
    Color::green, // Only argument that matters.
    0.0,  
    0.25, 
    0.25, 
    0.75, 
    0.5   
};

Resident_StepUp grNeighbor03{
    13,
    Color::green, // Only argument that matters.
    0.0,  
    0.25, 
    0.25, 
    0.75, 
    0.5   
};
    

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            1, 
            Color::green, 
            5.0, // allowedMovementDistance
            1.2, // happinessGoal
            0.0, // happinessValueAtZeroDiversity
            1.0, // diversityWhereDropHappens
            0.5 ),
        Contains("must be between 0.0 and 1.0 inclusive") 
    );

}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          -0.25,
                          0.0,
                          1.0,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at zero is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          -0.3,
                          0.0,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          1.2,
                          0.0,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at one is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          0.3,
                          -0.3,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          .5,
                          1.2,
                          0.5 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if diversityWhereRiseHappens is less than 0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          0.0,
                          1.0,
                          -1.0 ), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if diverstiyWhereRiseHappens is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          0.0,
                          1.0,
                          1.1), Contains("must be between 0.0 and 1.0 inclusive") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if"
" happinessValueAtZeroDiversity is larger than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            1, 
            Color::green, 
            5.0,
            0.25,
            .75,
            .25,
            0.5), 
        Contains("happinessAtZeroDiversity must be smaller than happinessAtOneDiversity.") );
}

TEST_CASE("Resident_StepUp Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(1, 
                          Color::green, 
                          5.0,
                          0.25,
                          .75,
                          .75,
                          0.5), Contains("happinessAtZeroDiversity must be"
                          " smaller than happinessAtOneDiversity.") );
}


TEST_CASE("getHappines() returns higher happinessValue at point where rise happens.")
{   
    // Note diversity Ratio is 0.5. @diverstiyWhereRiseHappens is 0.50.
    Resident_StepUp greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.50   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &grNeighbor01,
        &grNeighbor02,
        &blNeighbor01,
        &blNeighbor02
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.75);
}

TEST_CASE("getHappines() returns lower happinessValue before diversity drop.")
{
    // Note diversity Ratio is 0.25. @diverstiyWhereDropHappens is 0.5.
    Resident_StepUp blueResident{ 
        1, 
        Color::blue, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &blNeighbor01,
        &blNeighbor02,
        &blNeighbor03,
        &grNeighbor01
    };

    REQUIRE(blueResident.calculateHappiness(neighbors, 4) == 0.25);
}

TEST_CASE("getHappines() returns higher happinessValue afterDiversity drop.")
{
    // Note diversity Ratio is 0.75. @diverstiyWhereDropHappens is 0.25.
    Resident_StepUp blueResident{ 
        1, 
        Color::blue, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &blNeighbor01,
        &grNeighbor01,
        &grNeighbor02,
        &grNeighbor03,
    };

    REQUIRE(blueResident.calculateHappiness(neighbors, 4) == 0.75);
}

TEST_CASE("Resident_StepUp toStrBasic()")
{
    Resident_StepUp greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance (doesn't matter)
        0.25, // happinessGoal (doesn't matter)
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_StepUp(id, clr, mov, goal, hap0, hap1, rise):"
        " (1, green, 0.000000, 0.250000, 0.250000, 0.750000, 0.500000)");
}