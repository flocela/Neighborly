#include "catch.hpp"
#include "../src/Resident_Flat.h"
using Catch::Matchers::Contains;

TEST_CASE("Resident_Flat Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Flat( 1,
                       Color::green,
                       1.0,
                       1.2,
                       0.25 ), 
                       Contains("HappinessGoal must be between 0.0 and 1.0 inclusive.") );
}


TEST_CASE("Resident_Flat Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_Flat( 1,
                       Color::green,
                       1.0,
                       -0.1,
                       0.25 ), 
                       Contains("HappinessGoal must be between 0.0 and 1.0 inclusive.") );
}

TEST_CASE("Resident_Flat Ctor throws exception if happinessValue is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Flat( 1, 
                       Color::green,
                       1.0,
                       1.0,
                       1.2 ), Contains("HappinessValue must be between 0.0 and 1.0 inclusive.") );
}

TEST_CASE("Resident_Flat Ctor throws exception if happinessValue is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(Resident_Flat( 1, 
                                       Color::green,
                                       1.0,
                                       1.0,
                                       -.25 ), Contains("must be between 0.0 and 1.0 inclusive") );
}


TEST_CASE("getHappines() returns happinessValue")
{
    Resident_Flat resident { 1,
                            Color::green,
                            1.0,
                            1.0,
                            0.25 };
    std::vector<Color> neighbors = {Color::blue, Color::blue};
}