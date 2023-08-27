#include "catch.hpp"

#include <sstream>
#include "../src/Coordinate.h"

using namespace std;

TEST_CASE("less-than-opertor's primary axis is the y axis")
{
    Coordinate a{10, 1};
    Coordinate b{8, 2};

    REQUIRE(a < b);
}

TEST_CASE("less-than-opertor's secondary axis is the x axis")
{
    Coordinate a{10, 1};
    Coordinate b{8, 1};

    REQUIRE(b < a);
}

TEST_CASE("less-than-opertor:: a is not less than a")
{
    Coordinate a{10, 1};

    REQUIRE(!(a < a));
}

TEST_CASE("vector is sorted because operator< has been overriden")
{
    Coordinate a{10, 1};
    Coordinate b{8, 1};
    Coordinate c{5, 3};
    Coordinate d{20, 2};
    
    vector<Coordinate> coordinates = {a, b, c, d};
    sort(coordinates.begin(), coordinates.end());
    REQUIRE(8 == coordinates[0].getX());
    REQUIRE(10 ==coordinates[1].getX());
    REQUIRE(20 == coordinates[2].getX());
    REQUIRE(5 == coordinates[3].getX());
}

TEST_CASE("ostream operator")
{
    Coordinate a{10, 1};
    stringstream out;
    out << a;
    REQUIRE("(10, 1)" == out.str());
}

TEST_CASE("operator==")
{
    Coordinate a{10, 1};
    Coordinate b{10, 1};
    Coordinate c{20, 1};
    Coordinate d{10, 2};
    Coordinate e{20, 20};

    REQUIRE(a == a);
    REQUIRE(a == b);
    REQUIRE(!(a == c));
    REQUIRE(!(a == d));
    REQUIRE(!(a == e));
}

TEST_CASE("operator!=")
{
    Coordinate a{10, 1};
    Coordinate b{10, 1};
    Coordinate c{20, 1};
    Coordinate d{10, 2};
    Coordinate e{20, 20};

    REQUIRE(!(a != a));
    REQUIRE(!(a != b));
    REQUIRE(a != c);
    REQUIRE(a != d);
    REQUIRE(a != e);
}
