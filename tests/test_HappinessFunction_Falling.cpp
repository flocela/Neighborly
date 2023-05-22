#include "catch.hpp"
#include "../src/HappinessFunc_Falling.h"

using Catch::Matchers::Contains;

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when value at zero percent diversity is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, -.1, 0.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when value at zero percent diversity is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 110, 0.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when value at 100 percent diversity is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 10.0, -0.1), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when value at 100 percent diversity is greater than 100.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 10.0, 130), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when value at 0.0 diversity is greater than value at 100.0 percent."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 10.0, 1.0), 
        Contains("happinessAtZeroDiversity must be"
        " larger than happinessAt100Diversity.") 
    );
}

TEST_CASE(
    "getLargestValue, case should return value for no neighbors."
)
{
    HappinessFunc_Falling func(95, 70, 90);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "getLargestValue, case should return value for 100 percent diversity."
)
{
    HappinessFunc_Falling func(90, 70, 95);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE(
    "getSmallestValue, case should return value for no neighbors."
)
{
    HappinessFunc_Falling func(0, 20, 90);
    REQUIRE(0 == func.getSmallestValue());
}

TEST_CASE(
    "getSmallestValue, case should return value for 0 percent diversity."
)
{
    HappinessFunc_Falling func(10, 5, 90);
    REQUIRE(5.0 == func.getSmallestValue());
}

TEST_CASE(
    "calcHappiness(), fifty percent diversity"
)
{
    HappinessFunc_Falling func(10, 0, 100);
    REQUIRE(50 == func.calcHappiness(10, 4, 4));
}

TEST_CASE(
    "calcHappiness with no neighbors"
)
{
    HappinessFunc_Falling func(10, 0, 100);
    REQUIRE(10 == func.calcHappiness(10, 0, 0));
}
