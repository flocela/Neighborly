#include "catch.hpp"
#include "../src/AxisTopToBottomL.h"

TEST_CASE("AxisTopToBottomL.getLabelLengthPx()")
{
   AxisFormat format{};
    AxisTopToBottomL axis {
        format,
        0, // x coord where x and y axes meet
        0, // y coord where x and y axes meet
        0, // minVal
        0, // maxVal
        0, // pxPerUnit
        0, // tickThickness
        0, // start offset multiplier
        0  // end offset multplier
    };

    // label includes the number, the tick length outside the chart, the space between
    // the label and the tick length and also the thickness of the axis..
    int labelLength = 
        (3) * format.labelWidthMultiplier() * format.labelHeightPx() +
        3 + // text spacer defaults to 3
        format.majTickLengthOutsideChartPx() +
        format.axisThicknessPx();

    REQUIRE ( labelLength == axis.getLabelLengthPx() );
}