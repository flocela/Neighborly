#include "catch.hpp"
#include "../src/HappinessFunc_StepUp.h"

using Catch::Matchers::Contains;

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
    " happinessAtStart is larger than happinessAtEnd."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.0, 100, 50, .5), 
        Contains("happinessAtStart must be less than happinessAtEnd.") 
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
    "HappinessFunc_StepUp getLargestValue(),"
    " since happinessWithZeroNeighbors is larger than happinessAtEnd, getLargestValue() "
    " should return value for no neighbors."
)
{
    HappinessFunc_StepUp func(95, 0, 90, .5);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp getLargestValue()"
    " since happinessAtEnd is larger than happinessWithZeroNeighbors, getLargestValue() "
    " should return happinessAtEnd."
)
{
    HappinessFunc_StepUp func(90, 0, 95, .5);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp getSmallestValue(),"
    " since happinessAtStart is smaller than happinessWithZeroNeighbors, getSmallestValue() "
    " should return happinessAtStart."
)
{
    HappinessFunc_StepUp func(10, 0, 100, .5);
    REQUIRE(0.0 == func.getSmallestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp getSmallestValue(),"
    " since happinessWithZeroNeighbors is smaller than happinessAtStart, getSmallestValue() "
    " should return happinessWithZeroNeighbor."
)
{
    HappinessFunc_StepUp func(0.0, 10, 100, .5);
    REQUIRE(0.0 == func.getSmallestValue());
}

TEST_CASE(
    "HappinessFunc_StepUp calcHappiness() at stepdown is same as happinessAtStart"
)
{
    HappinessFunc_StepUp func(10, 0, 100.0, .5);
    REQUIRE(0.0 == func.calcHappiness(10, 4, 4));
}

TEST_CASE(
    "HappinessFunc_StepUp calcHappiness() before stepdown is same as happinessAtStart"
)
{
    HappinessFunc_StepUp func(10, 0, 100, .5);
    REQUIRE(0 == func.calcHappiness(10, 4, 2));
}

TEST_CASE(
    "HappinessFunc_StepUp calcHappiness() after stepdown is same as happinessAtEnd"
)
{
    HappinessFunc_StepUp func(0, 0, 100, .5);
    REQUIRE(100.0 == func.calcHappiness(10, 4, 6));
}

TEST_CASE(
    "HappinessFunc_StepUp calcHappiness with no neighbors"
)
{
    HappinessFunc_StepUp func(10, 0, 100, .5);
    REQUIRE(10 == func.calcHappiness(10, 0, 0));
}
