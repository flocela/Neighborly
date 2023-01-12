#include "catch.hpp"
#include "../src/HappinessFunc_StepUp.h"

using Catch::Matchers::Contains;
/*
TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when starting value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(-0.1, 0.2, 0.75), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when starting value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(1.1, 0.0, 0.75), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when ending value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.2, -0.1, 0.75), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when ending value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(.2, 1.1, 0.75), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when stepUpHappensAt location is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(.2, .75, -.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when stepUpHappensAt location is greater than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.2, .75, 1.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp Constructor throws invalid argument exception"
    "when starting value is greater than ending value"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepUp(0.9, 0.2, 0.5), 
        Contains("happinessAtZeroDiversity must be smaller than"
        " happinessAtOneDiversity.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepUp getHappiness()"
)
{   
    HappinessFunc_StepUp hf{0.1, 0.9, 0.75}; 
    REQUIRE(hf.getHappiness(10, 8, 2) == .1);
    REQUIRE(hf.getHappiness(4, 1, 3) == .9);
    REQUIRE(hf.getHappiness(10, 1, 8) == .9);
}
*/