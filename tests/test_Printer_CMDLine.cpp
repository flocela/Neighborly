#include "catch.hpp"
#include "../src/Coordinate.h"
#include <vector>
#include <algorithm>
#include <iostream>


// TODO probably delete this test case
TEST_CASE("print out an empty city")
{
    Coordinate a{10, 1};
    Coordinate b{8, 2};

    REQUIRE(a < b);
}


