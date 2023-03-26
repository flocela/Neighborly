#include "catch.hpp"
#include "../src/AxisFormat.h"

#include <math.h>

TEST_CASE("setLabelLetterHeight() with value less than one")
{
    AxisFormat af{};
    af.setLabelLetterHeight(-1);
    REQUIRE (af.labelHeightPx() == 1);
}

TEST_CASE("setLabelLetterSpace with value less than zero")
{
    AxisFormat af{};
    af.setLabelSpacePx(-1);
    REQUIRE (af.labelLineSpacePx() == 0);
}

TEST_CASE("setMajTickLengthPx to zero if less than zero")
{
    AxisFormat af{};
    af.setMajTickLengthPx(-1);
    REQUIRE (af.majTickLengthPx() == 0);
}

TEST_CASE("setMinTickLengthPx to zero if less than zero")
{
    AxisFormat af{};
    af.setMinTickLengthPx(-1);
    REQUIRE (af.minTickLengthPx() == 0);
}

TEST_CASE("setTickLengthInsideChartPx to zero if less than zero")
{
    AxisFormat af{};
    af.setTickLengthInsideChartPx(-1);
    REQUIRE (af.tickLengthInsideChartPx() == 0);
}