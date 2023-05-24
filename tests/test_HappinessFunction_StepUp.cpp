#include "catch.hpp"
#include "../src/HappinessFunc_StepUp.h"

using Catch::Matchers::Contains;
/*
TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " happinessAtStart is less than zero"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.0, -.1, 0.0, 0.5), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " happinessAtStart is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.0, 110, 100, 0.5), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " happinessAtEnd is less than zero"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.0, 10.0, -0.1, 0.5),
        Contains("must be between 0.0 and 100.0 inclusive")
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " happinessAtEnd is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.0, 10.0, 130, 0.5), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " happinessAtEnd is larger than happinessAtStart."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.0, 50, 100, .5), 
        Contains("starting happiness value must be larger than ending happiness value.") 
    );
}


TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " value for no neighbors is less than zero."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(-1, 100, 0, .5), 
        Contains("must be between 0.0 and 100.0 inclusive.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception when"
    " value for no neighbors is greater than 100."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(110, 100, 0, .5), 
        Contains("must be between 0.0 and 100.0 inclusive.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp getLargestValue(), case"
    " should return value for no neighbors."
)
{
    HappinessFunc_StepUp func(95, 90, 0, .5);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp getLargestValue(), case"
    " should return value for zero percent diversity."
)
{
    HappinessFunc_StepUp func(90, 95, 0, .5);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp getSmallestValue(), case"
    " should return value for no neighbors."
)
{
    HappinessFunc_StepUp func(0, 90, 20, .5);
    REQUIRE(0.0 == func.getSmallestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp getSmallestValue(), case"
    " should return value for 100 percent diversity."
)
{
    HappinessFunc_StepUp func(50, 90, 20, .5);
    REQUIRE(20.0 == func.getSmallestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp calcHappiness() at stepdown is same as happinessAtStart"
)
{
    HappinessFunc_StepUp func(0, 100, 0, .5);
    REQUIRE(100 == func.calcHappiness(10, 4, 4));
}


TEST_CASE(
    "HappinessFunc_StepUp calcHappiness() before stepdown is same as happinessAtStart"
)
{
    HappinessFunc_StepUp func(0, 100, 0, .5);
    REQUIRE(100 == func.calcHappiness(10, 4, 2));
}


TEST_CASE(
    "HappinessFunc_StepUp calcHappiness() after stepdown is same as happinessAtEnd"
)
{
    HappinessFunc_StepUp func(0, 100, 0, .5);
    REQUIRE(0.0 == func.calcHappiness(10, 4, 6));
}


TEST_CASE(
    "HappinessFunc_StepUp calcHappiness with no neighbors"
)
{
    HappinessFunc_StepUp func(10, 100, 0, .5);
    REQUIRE(10 == func.calcHappiness(10, 0, 0));
}
*/