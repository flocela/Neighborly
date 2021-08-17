#include "catch.hpp"
#include "../src/Resident_StepUp.h"
#include "../src/Resident_Flat.h"
using Catch::Matchers::Contains;


// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blNeighbor01{1, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blNeighbor02{2, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blNeighbor03{3, Color::blue, 0.0, 0.0, 0.0 };
    
Resident_Flat grNeighbor01{1, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat grNeighbor02{2, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat grNeighbor03{3, Color::green, 0.0, 0.0, 0.0 };
    

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            1.2, // happinessGoal
            0.0,
            .1,
            0.2
        ),
        Contains("must be between 0.0 and 1.0 inclusive") 
    );

}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            -.1, // happinessGoal
            0.1,
            0.2,
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            -.1, // happinessValueAtZeroDiversity 
            .1,
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            1.2, // happinessValueAtZeroDiversity 
            .1,
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at one is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            0.2,  
            -.1, // happinessValueAtOneDiversity
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            0.2,  
            1.1, // happinessValueAtOneDiversity
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if diversityWhereRiseHappens is less than 0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            0.1,  
            0.2,
            -.1 // diversityWhereRiseHappens
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if diverstiyWhereRiseHappens is greater than 1.0.")
{   
   REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            0.1,  
            0.2,
            1.1 // diversityWhereRiseHappens
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if"
" happinessValueAtZeroDiversity is larger than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            .75, //happinessValueAtZeroDiversity
            .25, //happinessValueAtOneDiversity
            0), 
        Contains("happinessAtZeroDiversity must be smaller than"
            " happinessAtOneDiversity.")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            0,
            .75, // happinessValueAtZeroDiversity
            .75, // happinessValueAtOneDiversity
            0), 
        Contains("happinessAtZeroDiversity must be smaller than"
            " happinessAtOneDiversity.")
    );
}

TEST_CASE("getHappines() returns higher happinessValue at point where rise happens.")
{   
    // Note @diverstiyWhereRiseHappens is 0.50.
    Resident_StepUp greenResident{ 
        0, 
        Color::green, 
        0.0,  
        0.25,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.50  // diversityWhereRiseHappens
    };

    // diversity Ratio is 0.5.
    std::set<Resident*> neighbors = { 
        &grNeighbor01,
        &grNeighbor02,
        &blNeighbor01,
        &blNeighbor02
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.75);
}

TEST_CASE("getHappines() returns lower happinessValue before diversity rise.")
{
    // Note @diverstiyWhereRiseHappens is 0.5.
    Resident_StepUp blueResident{ 
        0, 
        Color::blue, 
        0.0,  
        0.0, 
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };

    // Diversity Ratio is 0.25. 
    std::set<Resident*> neighbors = { 
        &blNeighbor01,
        &blNeighbor02,
        &blNeighbor03,
        &grNeighbor01
    };

    REQUIRE(blueResident.calculateHappiness(neighbors, 4) == 0.25);
}

TEST_CASE("getHappiness() returns higher happinessValue afterDiversity rise.")
{
    // Note @diverstiyWhereDropHappens is 0.5.
    Resident_StepUp blueResident{ 
        0, 
        Color::blue, 
        0.0, 
        0.0,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };

    // Diversity Ratio is 0.75.
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
        0.0,  // allowedMovementDistance 
        0.25, // happinessGoal
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_StepUp(id, clr, mov, goal, hap0, hap1, rise):"
        " (1, green, 0.000000, 0.250000, 0.250000, 0.750000, 0.500000)");
}