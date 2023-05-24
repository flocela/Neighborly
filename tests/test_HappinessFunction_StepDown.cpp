#include "catch.hpp"
#include "../src/HappinessFunc_StepDown.h"

using Catch::Matchers::Contains;

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " happinessAtStart is less than zero"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(0.0, -.1, 0.0, 0.5), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " happinessAtStart is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(0.0, 110, 100, 0.5), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " happinessAtEnd is less than zero"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(0.0, 10.0, -0.1, 0.5),
        Contains("must be between 0.0 and 100.0 inclusive")
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " happinessAtEnd is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(0.0, 10.0, 130, 0.5), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " happinessAtEnd is larger than happinessAtStart."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(0.0, 50, 100, .5), 
        Contains("starting happiness value must be larger than ending happiness value.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " value for no neighbors is less than zero."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(-1, 100, 0, .5), 
        Contains("must be between 0.0 and 100.0 inclusive.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception when"
    " value for no neighbors is greater than 100."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(110, 100, 0, .5), 
        Contains("must be between 0.0 and 100.0 inclusive.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown getLargestValue(), "
    " since happinessWithNoNeighbors is larger than happinessAtStart, getLargest()"
    " should return value for no neighbors,"
    
)
{
    HappinessFunc_StepDown func(95, 90, 0, .5);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "HappinessFunc_StepDown getLargestValue(),"
    " since happinessAtStart is larger than happinessWithNoNeighbors, getLargest()"
    " should return value happinessAtStart."
)
{
    HappinessFunc_StepDown func(90, 95, 0, .5);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "HappinessFunc_StepDown getSmallestValue(),"
    " since happinessWithZeroNeighbors is less than happinessAtEnd, getSmallestValue()"
    " should return value for no neighbors."
)
{
    HappinessFunc_StepDown func(0, 90, 20, .5);
    REQUIRE(0.0 == func.getSmallestValue());
}

TEST_CASE(
    "HappinessFunc_StepDown getSmallestValue(),"
    " since happinessAtEnd is less than happinessWithZeroNieghbors, getSmallestValue()"
    " should return happinessAtEnd."
)
{
    HappinessFunc_StepDown func(50, 90, 20, .5);
    REQUIRE(20.0 == func.getSmallestValue());
}

TEST_CASE(
    "HappinessFunc_StepDown calcHappiness() at stepdown is same as happinessAtStart"
)
{
    HappinessFunc_StepDown func(0, 100, 0, .5);
    REQUIRE(100 == func.calcHappiness(10, 4, 4));
}

TEST_CASE(
    "HappinessFunc_StepDown calcHappiness() before stepdown is same as happinessAtStart"
)
{
    HappinessFunc_StepDown func(0, 100, 0, .5);
    REQUIRE(100 == func.calcHappiness(10, 4, 2));
}

TEST_CASE(
    "HappinessFunc_StepDown calcHappiness() after stepdown is same as happinessAtEnd"
)
{
    HappinessFunc_StepDown func(0, 100, 0, .5);
    REQUIRE(0.0 == func.calcHappiness(10, 4, 6));
}

TEST_CASE(
    "HappinessFunc_StepDown calcHappiness with no neighbors"
)
{
    HappinessFunc_StepDown func(10, 100, 0, .5);
    REQUIRE(10 == func.calcHappiness(10, 0, 0));
}