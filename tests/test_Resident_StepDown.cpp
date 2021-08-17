#include "catch.hpp"
#include "../src/Resident_StepDown.h"
#include "../src/Resident_Flat.h"
#include <set>
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor1{1, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor2{2, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor3{3, Color::blue, 0.0, 0.0, 0.0 };
    
Resident_Flat greenNeighbor1{1, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor2{2, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor3{3, Color::green, 0.0, 0.0, 0.0 };
    

TEST_CASE("Resident_StepDown Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            1.2, //happinessGoal
            0.2, 
            0.1,
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            -0.1, //happinessGoal 
            0.2, 
            0.1,
            0.0 
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            -0.2, // happinessValueAtZeroDiversity
            0.1,
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            1.2, // happinessValueAtZeroDiversity
            0.1,
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at one is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            0.2, 
            -0.1, // happinessValueAtOneDiversity
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            0.2, 
            1.1, // happinessValueAtOneDiversity
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if diverstiyWhereDropHappens is less than 0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            0.2, 
            0.1,
            -0.1 //diversityWhereDropHappens
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if diverstiyWhereDropHappens is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            0.2, 
            0.1,
            1.1 //diversityWhereDropHappens
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if"
" happinessValueAtZeroDiversity is smaller than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            0.1, //happinessValueAtZeroDiversity
            0.2, //happinessValueAtOneDiversity
            0.0 
        ),
        Contains(
            "happinessAtZeroDiversity must be"
            " larger than happinessAtOneDiversity."
        )
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            Color::green, 
            0.0, 
            0.0,
            0.2, //happinessValueAtZeroDiversity
            0.2, //happinessValueAtOneDiversity
            0.0 
        ),
        Contains(
            "happinessAtZeroDiversity must be"
            " larger than happinessAtOneDiversity."
        )
    );
}

TEST_CASE("getHappiness() returns lowered happinessValue at point where drop happens.")
{
    // Note diversity Ratio is 0.25. @diverstiyWhereDropHappens is 0.25.
    Resident_StepDown greenResident{ 
        0, 
        Color::green, 
        0.0,  
        0.0,
        0.2, // happinessValueAtZeroDiversity
        0.1, // happinessValueAtOneDiversity
        0.25  // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &greenNeighbor1,
        &greenNeighbor2,
        &greenNeighbor3,
        &blueNeighbor1
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.1);
}

TEST_CASE("getHappiness() returns higher happinessValue before diversity drop.")
{
    // Note diversity Ratio is 0.25. @diverstiyWhereDropHappens is 0.5.
    Resident_StepDown greenResident{ 
        0, 
        Color::green, 
        0.0,  
        0.0, 
        0.2, // happinessValueAtZeroDiversity
        0.1, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };

    std::set<Resident*> neighbors = { 
        &blueNeighbor1,
        &greenNeighbor1,
        &greenNeighbor2,
        &greenNeighbor3
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.2);
}

TEST_CASE("getHappines() returns lower happinessValue afterDiversity drop.")
{
    // Note diversity Ratio is 0.25. @diverstiyWhereDropHappens is 0.25.
    Resident_StepDown greenResident{ 
        0, 
        Color::green, 
        0.0, 
        0.0,
        0.2,
        0.1,
        0.5
    };

    std::set<Resident*> neighbors = { 
        &blueNeighbor1,
        &blueNeighbor2,
        &blueNeighbor3,
        &greenNeighbor1,
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.1);
}

TEST_CASE("Resident_StepDown toStrBasic()")
{
    Resident_StepDown greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowedMovementDistance
        0.25, // happinessGoal
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_StepDown(id, clr, mov, goal, hap0, hap1, drop):"
        " (1, green, 0.000000, 0.250000, 0.750000, 0.250000, 0.500000)");
}
