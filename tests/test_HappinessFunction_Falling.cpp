#include "catch.hpp"

#include "../src/HappinessFunc_Falling.h"

using Catch::Matchers::Contains;

TEST_CASE("HappinessFunc_Falling:: Constructor throws invalid argument exception when"
    " value at zero percent diversity is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, -.1, 0.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Falling:: Constructor throws invalid argument exception when"
    " value at zero percent diversity is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 110, 10), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Falling:: Constructor throws invalid argument exception when"
    " value at 100 percent diversity is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 10.0, -0.1),
        Contains("must be between 0.0 and 100.0 inclusive")
    );
}

TEST_CASE("HappinessFunc_Falling:: Constructor throws invalid argument exception when"
    " value at 100 percent diversity is greater than 100.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 10.0, 130), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Falling:: Constructor throws invalid argument exception when"
    " value at 0.0 diversity is less than value at 100.0 percent."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.0, 9.0, 10), 
        Contains("happinessAtZeroDiversity must be larger than happinessAtOneDiversity.") 
    );
}

TEST_CASE("HappinessFunc_Falling::  getLargestValue(),"
    " since value for no neighbors is larger than happinessAtZero, getLargestValue()"
    " should return value for no neighbors."
)
{
    HappinessFunc_Falling func(5, 90, 10);
    REQUIRE(90 == func.getLargestValue());
}

TEST_CASE("HappinessFunc_Falling:: getLargestValue(),"
    " since value at zero diversity is larger than value for no neighbors, getLargestValue() "
    " should return value for zero percent diversity."
)
{
    HappinessFunc_Falling func(90, 95, 10);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE("HappinessFunc_Falling:: getSmallestValue(),"
    " since value for no neighbors is smaller than value at 100 percent diversity, getSmallest()"
    " should return value for no neighbors."
)
{
    HappinessFunc_Falling func(10, 90, 20);
    REQUIRE(10 == func.getSmallestValue());
}

TEST_CASE("HappinessFunc_Falling:: getSmallestValue(),"
    " since value at 100 percent diversity is smaller than value for no neigbors, getSmallest()"
    " should return value for 100 percent diversity."
)
{
    HappinessFunc_Falling func(30, 90, 20);
    REQUIRE(20 == func.getSmallestValue());
}

TEST_CASE("HappinessFunc_Falling:: calcHappiness(), fifty percent diversity"
)
{
    HappinessFunc_Falling func(10, 100, 0);
    REQUIRE(50 == func.calcHappiness(10, 4, 4));
}

TEST_CASE("HappinessFunc_Falling:: calcHappiness with no neighbors"
)
{
    HappinessFunc_Falling func(10, 100, 0);
    REQUIRE( 10 == func.calcHappiness(10, 0, 0));
}
