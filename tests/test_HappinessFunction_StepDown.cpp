#include "catch.hpp"
#include "../src/HappinessFunc_StepDown.h"

using Catch::Matchers::Contains;
/*
TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when starting value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(-0.1, 0.0, 0.5), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when starting value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(1.1, 0.0, 0.5), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when ending value is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(1.0, -0.1, 0.5), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when ending value is greater than 1.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(1.0, 1.1, 0.5), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when stepDownHappensAt location is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(1.0, .75, -.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}


TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when stepDownHappensAt location is greater than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(1.0, .75, 1.1), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown Constructor throws invalid argument exception"
    "when starting value is less than ending value"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_StepDown(0.1, 0.9, 0.5), 
        Contains("happinessAtZeroDiversity must be larger than"
        " happinessAtOneDiversity.") 
    );
}

TEST_CASE(
    "HappinessFunc_StepDown getHappiness()"
)
{   
    HappinessFunc_StepDown hf{0.9, 0.1, 0.75}; 
    REQUIRE(hf.getHappiness(10, 8, 2) == .9);
    REQUIRE(hf.getHappiness(4, 1, 3) == .1);
    REQUIRE(hf.getHappiness(10, 1, 8) == .1);
}*/