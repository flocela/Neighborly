#include "catch.hpp"
#include "../src/HappinessFunc_Flat.h"
#include <iostream>

using Catch::Matchers::Contains;

TEST_CASE("HappinessFunc_Flat:: Constructor throws invalid argument exception"
    "when happiness value is less than 0.0"
)
{  
    REQUIRE_THROWS_WITH(
        HappinessFunc_Flat(0.0, -0.1), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Flat:: Constructor throws invalid argument exception"
    "when happiness value is greater than 100.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Flat(0.0, 110), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Flat:: Constructor throws invalid argument exception"
    "when happiness value for no neighbors is < 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Flat(-1, 0.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}


TEST_CASE("HappinessFunc_Flat:: Constructor throws invalid argument exception"
    "when happiness value for no neighbors is > 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Flat(110, 0.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Flat:: getLargestValue() should return constant value."
)
{
    HappinessFunc_Flat f(10, 100);
    REQUIRE(100 == f.getLargestValue());
}


TEST_CASE("HappinessFunc_Flat:: getLargestValue() should return value for no neighbors."
)
{
    HappinessFunc_Flat f(100, 50);
    REQUIRE(100 == f.getLargestValue());
}

TEST_CASE("HappinessFunc_Flat:: getSmallestValue() should return constant value."
)
{
    HappinessFunc_Flat f(10, 0);
    REQUIRE(0 == f.getSmallestValue());
}


TEST_CASE("HappinessFunc_Flat:: getSmallestValue() should return value for no neighbors."
)
{
    HappinessFunc_Flat f(0, 50);
    REQUIRE(0 == f.getSmallestValue());
}

TEST_CASE("HappinessFunc_Flat:: getHappiness with no neighbors"
)
{
    HappinessFunc_Flat hf{50, 90};
    REQUIRE( hf.calcHappiness(4, 0, 0) == 50 );
}


TEST_CASE("HappinessFunc_Flat:: getHappiness should be 90, because happiness value is constant."
)
{
    HappinessFunc_Flat hf{50, 90};
    REQUIRE( hf.calcHappiness(4, 0, 4) == 90 );
}
