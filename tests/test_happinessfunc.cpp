#include "catch.hpp"
#include "../src/HappinessFunc_Flat.h"
#include "../src/HappinessFunc_Rising.h"
#include "../src/HappinessFunc_StepDown.h"

using Catch::Matchers::Contains;

// Run from the command line:
// g++ --std=c++17 -o runme ../src/happinessfunc_flat.cpp ../src/happinessfunc_stepdown.cpp ../src/happinessfunc_rising.cpp happinessfunc_test.cpp test_main.o

TEST_CASE("HappinessFuncFlat Constructor throws invalid argument exception", "[happinessfunc_flat]")
{   
    REQUIRE_THROWS_WITH(HappinessFunc_Flat(1.1), Contains("must be between 0.0 and 1.0 inclusive") );
    REQUIRE_THROWS_WITH(HappinessFunc_Flat(-0.2), Contains("must be between 0.0 and 1.0 inclusive"));
}


TEST_CASE("HappinessFuncFlat getHappiness() returns correct happiness", "[happinessfunc_flat]")
{
    HappinessFunc_Flat funcZero{0};
    HappinessFunc_Flat funcQuarter{0.25};
    HappinessFunc_Flat funcOne{1};

    REQUIRE( funcZero.getHappiness(4, 2, 2)    == 0);
    REQUIRE( funcQuarter.getHappiness(4, 2, 2) == 0.25);
    REQUIRE( funcOne.getHappiness(4, 2, 2)     == 1);
}

TEST_CASE("HappinessFuncRising Constructor throws invalid argument exception", "[happinessfunc_rising]")
{   
    REQUIRE_THROWS_WITH(HappinessFunc_Rising(0.0, 1.1), Contains("must be between 0.0 and 1.0 inclusive"));
    REQUIRE_THROWS_WITH(HappinessFunc_Rising(-0.2, 1.0), Contains("must be between 0.0 and 1.0 inclusive"));
    REQUIRE_THROWS_WITH(HappinessFunc_Rising(0.5, 0.2), Contains("hapinessAtOneDiversity must be larger than at happinessAtZeroDiversity"));
}

TEST_CASE("HappinessFuncRising getHappiness()", "[happinessfuncrising]")
{
    HappinessFunc_Rising funcRising{.5, 1.0};

    REQUIRE( funcRising.getHappiness(4, 2, 2) == 0.75);
}

TEST_CASE("HappinessFuncStepDown Constructor throws invalid argument exception", "[happinessfunc_stepdown]")
{
    REQUIRE_THROWS_WITH(HappinessFunc_StepDown(1.1, .5, .5), Contains("must be between 0.0 and 1.0 inclusive"));
    REQUIRE_THROWS_WITH(HappinessFunc_StepDown(0.5, 1.0, .5), Contains("happinessAtZeroDiversity must be larger than happinessAtOneDiversity"));
}

TEST_CASE("HappinessFuncStepDown getHappiness()", "[happinessfuncstepdown]")
{
    HappinessFunc_StepDown stepDownFunc{0.9, 0.25, 0.25};

    REQUIRE( stepDownFunc.getHappiness(4, 2, 2) == 0.25);
    REQUIRE( stepDownFunc.getHappiness(4, 3, 1) == 0.25);
    REQUIRE( stepDownFunc.getHappiness(16, 13, 3) == 0.9);
}

