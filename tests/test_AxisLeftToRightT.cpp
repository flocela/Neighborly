#include "catch.hpp"
#include "../src/AxisLeftToRightT.h"

TEST_CASE("AxisLeftToRightT.getLabelLengthPx()")
{
   AxisFormat format{};
    AxisLeftToRightT axis {
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

    // using default AxisFormat values
    // majTickLengthOutsideChart is maj tick length minus length inside chart minus axis thickness
    // (10 - 2 - 1 = 7)
    // label includes the number, the tick length outside the chart, the space between
    // the label and the tick length and also the thickness of the axis.
    int labelLength = 
        format.labelHeightPx() + // 22
        format.labelLineSpacePx() + // 2
        format.majTickLengthOutsideChartPx(); // 1

    REQUIRE ( labelLength == axis.getLabelLengthPx() );
    REQUIRE ( labelLength + format.axisThicknessPx() == axis.sizeYPx() );
}