#include "catch.hpp"
#include "../src/HappinessFunc_Rising.h"

using Catch::Matchers::Contains;

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value at zero percent diversity is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(0.0, -.1, 10.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value at zero percent diversity is greater than 100"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(0.0, 110, 100.0), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value at 100 percent diversity is less than 0.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(0.0, 10.0, -0.1), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value at 100 percent diversity is greater than 100.0"
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(0.0, 10.0, 130), 
        Contains("must be between 0.0 and 100.0 inclusive") 
    );
}

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value at zero diversity is greater than value at 100 percent diversity."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(0.0, 100, 50), 
        Contains("happinessAtOneDiversity must be"
        " larger than at happinessAtZeroDiversity.") 
    );
}

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value for no neighbors is less than zero."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(-1, 0, 100), 
        Contains("happiness value for no neighbors must be"
        " between 0.0 and 100.0 inclusive.") 
    );
}

TEST_CASE("HappinessFunc_Rising:: Constructor throws invalid argument exception when"
    " value for no neighbors is greater than 100."
)
{   
    REQUIRE_THROWS_WITH(
        HappinessFunc_Rising(110, 0, 100), 
        Contains("happiness value for no neighbors must be"
        " between 0.0 and 100.0 inclusive.") 
    );
}

TEST_CASE("HappinessFunc_Rising:: getLargestValue(), case"
    " should return value for no neighbors."
)
{
    HappinessFunc_Rising func(95, 70, 90);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE("HappinessFunc_Rising:: getLargestValue(), case"
    " should return value for 100 percent diversity."
)
{
    HappinessFunc_Rising func(90, 70, 95);
    REQUIRE(95 == func.getLargestValue());
}

TEST_CASE("HappinessFunc_Rising:: getSmallestValue(), case"
    " should return value for no neighbors."
)
{
    HappinessFunc_Rising func(0, 20, 90);
    REQUIRE(0 == func.getSmallestValue());
}

TEST_CASE("HappinessFunc_Rising:: getSmallestValue(), case"
    " should return value for 0 percent diversity."
)
{
    HappinessFunc_Rising func(10, 5, 90);
    REQUIRE(5.0 == func.getSmallestValue());
}

TEST_CASE("HappinessFunc_Rising:: calcHappiness(), fifty percent diversity"
)
{
    HappinessFunc_Rising func(10, 0, 100);
    REQUIRE(50 == func.calcHappiness(10, 4, 4));
}

TEST_CASE("HappinessFunc_Rising:: calcHappiness with no neighbors"
)
{
    HappinessFunc_Rising func(10, 0, 100);
    REQUIRE(10 == func.calcHappiness(10, 0, 0));
}
