#include "catch.hpp"
#include "../src/AxisFormat.h"

#include <math.h>

TEST_CASE("AxisFormat:: setLabelLetterHeight() with value less than one")
{
    AxisFormat af{};
    af.setLabelLetterHeight(-1);
    REQUIRE (1 == af.labelHeightPx());
}

TEST_CASE("AxisFormat:: setLabelLetterSpace with value less than zero")
{
    AxisFormat af{};
    af.setLabelSpacePx(-1);
    REQUIRE (0 == af.labelLineSpacePx());
}

TEST_CASE("AxisFormat:: setMajTickLengthPx to zero if less than zero")
{
    AxisFormat af{};
    af.setMajTickLengthPx(-1);
    REQUIRE (0 == af.majTickLengthPx());
}

TEST_CASE("AxisFormat:: setMinTickLengthPx to zero if less than zero")
{
    AxisFormat af{};
    af.setMinTickLengthPx(-1);
    REQUIRE (0 == af.minTickLengthPx());
}

TEST_CASE("AxisFormat:: setTickLengthInsideChartPx to zero if less than zero")
{
    AxisFormat af{};
    af.setTickLengthInsideChartPx(-1);
    REQUIRE (0 == af.tickLengthInsideChartPx());
}