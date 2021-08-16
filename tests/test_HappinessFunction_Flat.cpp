#include "catch.hpp"
#include "../src/HappinessFunc_Flat.h"
#include <iostream>

using Catch::Matchers::Contains;

TEST_CASE(
    "HappinessFunc_Flat Constructor throws invalid argument exception"
    "when happiness value is less than 0.0"
)
{  
    REQUIRE_THROWS_WITH(
        HappinessFunc_Flat(-0.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Flat Constructor throws invalid argument exception"
    "when happiness value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Flat(1.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Flat getHappiness"
)
{
    HappinessFunc_Flat hf{.75};
    REQUIRE( hf.getHappiness(4, 1, 3) == 0.75 );
}