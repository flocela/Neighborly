#include "catch.hpp"
#include "../src/HappinessFunc_Rising.h"

using Catch::Matchers::Contains;

TEST_CASE(
    "HappinessFunc_Rising Constructor throws invalid argument exception"
    "when starting value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(-0.1, 0.0), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Rising Constructor throws invalid argument exception"
    "when starting value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(1.1, 0.0), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Rising Constructor throws invalid argument exception"
    "when ending value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(1.0, -0.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Rising Constructor throws invalid argument exception"
    "when ending value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(1.0, 1.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_Rising Constructor throws invalid argument exception"
    "when starting value is greater than ending value"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(0.9, 0.1), 
        Contains("hapinessAtOneDiversity must be larger than at"
        " happinessAtZeroDiversity") 
    );
}

TEST_CASE(
    "HappinessFunc_Rising getHappiness"
)
{
    HappinessFunc_Rising hf{.2, .8};
    REQUIRE( (hf.getHappiness(4, 1, 3) - 0.65 ) < 0.001);
    REQUIRE( (hf.getHappiness(4, 1, 3) - 0.65 ) > -0.001);
}