#include "catch.hpp"
#include "../src/Resident_Falling.h"
#include "../src/Resident_Flat.h"
#include <set>
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor001{1, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor002{2, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor003{3, Color::blue, 0.0, 0.0, 0.0 };
    
Resident_Flat greenNeighbor001{1, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor002{2, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor003{3, Color::green, 0.0, 0.0, 0.0 };

TEST_CASE("Resident_Falling Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            -0.25, // happiness goal
            0.2,
            0.1
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
} 

TEST_CASE("Resident_Falling Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0, 
            1.2, // happiness goal
            0.2, 
            0.1 
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );

}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            0.0,
            -0.3, // value at zero Diversity
            0.1
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            0.0,
            1.2, // value at zero Diversity
            0.1
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at one is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            0.0,
            0.2,
            -0.3 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            0.0,
            0.2,
            1.2 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if"
" happinessValueAtZeroDiversity is smaller than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            0.0,
            .25, // value at zero Diversity
            .75  // value at one Diversity
        ), 
        Contains("happinessAtZeroDiversity must be"
        " larger than happinessAtOneDiversity.") );
}

TEST_CASE("Resident_Falling Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            Color::green, 
            0.0,
            0.0,
            .75,
            .75
        ), 
        Contains("happinessAtZeroDiversity must be"
        " larger than happinessAtOneDiversity.")
    );
}

TEST_CASE("getHappiness()")
{
    Resident_Falling greenResident{ 
        0, 
        Color::green, 
        0.0,  
        0.0, 
        0.8, // happinessValueAtZeroDiversity
        0.2, // happinessValueAtOneDiversity
    };

    std::set<Resident*> neighbors = { 
        &greenNeighbor001,
        &greenNeighbor002,
        &greenNeighbor003,
        &blueNeighbor001
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.65);
}

TEST_CASE("Resident_Falling toStrBasic()")
{
    Resident_Falling greenResident{ 
        1, 
        Color::green, 
        0.0,  
        0.25, 
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_Falling(id, clr, mov, goal, hap0, hap1):"
        " (1, green, 0.000000, 0.250000, 0.750000, 0.250000)");
}
