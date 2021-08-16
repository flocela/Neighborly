#include "catch.hpp"
#include "../src/HappinessFunc_Falling.h"

using Catch::Matchers::Contains;

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when starting value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(-0.1, 0.0), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when starting value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(1.1, 0.0), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when ending value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(1.0, -0.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when ending value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(1.0, 1.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling Constructor throws invalid argument exception"
    "when starting value is less than ending value"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Falling(0.1, 0.9), 
        Contains("happiness at Zero Diversity must be less than"
        "value at One Diversity.") 
    );
}

TEST_CASE(
    "HappinessFunc_Falling getHappiness"
)
{
    HappinessFunc_Falling hf{.5, .1};
    REQUIRE( (hf.getHappiness(4, 1, 3) - .2) < 0.001);
    REQUIRE( (hf.getHappiness(4, 1, 3) - .2) > -0.001);
}