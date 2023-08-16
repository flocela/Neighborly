#include "catch.hpp"

#include "../src/Axis_Basic.h"
#include "../src/GrAxisVerticalSimple.h"

using namespace std;

TEST_CASE("GrAxisVerticalSimple.getLabelLengthPx()")
{
   AxisFormat format{};

    GrAxisVerticalSimple grAxis {
        make_unique<Axis_Basic>(
            true,
            0,
            0,
            0,
            0,
            0,
            0),
        format,
        0
    };

    // Label is horizontal. It includes the number, the tick length outside the chart and the space
    // between the label and the tick.
    int labelLength = 
        (3) * format.labelWidthMultiplier() * format.labelHeightPx() +
        3 + // text spacer defaults to 3
        format.majTickLengthOutsideChartPx();

    REQUIRE ( labelLength == grAxis.getLabelLengthPx() );
    REQUIRE ( labelLength + format.axisThicknessPx() == grAxis.sizeXPx());
}