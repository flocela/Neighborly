#include "catch.hpp"

using Catch::Matchers::Contains;

#include "../src/House.h"

TEST_CASE("House:: toStr()")
{   
    House house (12);
    REQUIRE( house.toStr() == "House (addr): (12)");
}

TEST_CASE("House:: operator<")
{
    House h1(1);
    House h10(10);
    REQUIRE( (h1 < h10) == true);
}