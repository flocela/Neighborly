#include "catch.hpp"

using Catch::Matchers::Contains;

#include <iostream>
#include "../src/House.h"

TEST_CASE("House toStr ()")
{   
    House house (12);
    REQUIRE( house.toStr() == "House (addr): (12)");
}