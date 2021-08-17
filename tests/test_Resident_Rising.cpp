#include "catch.hpp"
#include "../src/Resident_Rising.h"
#include "../src/Resident_Flat.h"
#include <set>
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor0001{1, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor0002{2, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor0003{3, Color::blue, 0.0, 0.0, 0.0 };
    
Resident_Flat greenNeighbor0001{1, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor0002{2, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor0003{3, Color::green, 0.0, 0.0, 0.0 };

TEST_CASE("Resident_Rising Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            -0.25, // happiness goal
            0.1,
            0.2
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
} 

TEST_CASE("Resident_Rising Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0, 
            1.2, // happiness goal
            0.1, 
            0.2 
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );

}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            0.0,
            -0.3, // value at zero Diversity
            0.2
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            0.0,
            1.2, // value at zero Diversity
            0.2
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at one is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            0.0,
            0.1,
            -0.3 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            0.0,
            0.1,
            1.2 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if"
" happinessValueAtZeroDiversity is larger than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            0.0,
            .2, // value at zero Diversity
            .1  // value at one Diversity
        ), 
        Contains("hapinessAtOneDiversity must be larger than at"
            " happinessAtZeroDiversity."
        )
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            Color::green, 
            0.0,
            0.0,
            .75,
            .75
        ), 
        Contains("hapinessAtOneDiversity must be larger than at"
            " happinessAtZeroDiversity.")
    );
}

TEST_CASE("Residnt_Rising getHappiness()")
{
    Resident_Rising greenResident{ 
        0, 
        Color::green, 
        0.0,  
        0.0, 
        0.2, // happinessValueAtZeroDiversity
        0.8, // happinessValueAtOneDiversity
    };

    std::set<Resident*> neighbors = { 
        &greenNeighbor0001,
        &greenNeighbor0002,
        &greenNeighbor0003,
        &blueNeighbor0001
    };

    REQUIRE(( greenResident.calculateHappiness(neighbors, 4) - 0.35) > -0.001);
    REQUIRE(( greenResident.calculateHappiness(neighbors, 4) - 0.35) < 0.001);
}

TEST_CASE("Resident_Rising toStrBasic()")
{
    Resident_Rising greenResident{ 
        1, 
        Color::green, 
        0.0,  
        0.25, 
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_Rising(id, clr, mov, goal, hap0, hap1):"
        " (1, green, 0.000000, 0.250000, 0.250000, 0.750000)");
}
