#include "catch.hpp"

#include "../src/Axis_Basic.h"
#include "../src/GrAxisHorizontalSimple.h"

using namespace std;

TEST_CASE("GrAxisHorizontalSimple.getLabelLengthPx()")
{
   AxisFormat format{};

    GrAxisHorizontalSimple grAxis {
        make_unique<Axis_Basic>(
            true,
            0,
            0,
            0,
            0,
            0,
            0),
        format,
        0,
        true
    };

    // Label length is vertical. It includes the number height, the tick length outside the
    // chart and the space between the label and the tick.
    int labelLength = 
        format.labelHeightPx() + // 22
        format.labelLineSpacePx() + // 2
        format.majTickLengthOutsideChartPx(); // 1

    REQUIRE ( labelLength == grAxis.getLabelLengthPx() );
    
    REQUIRE ( labelLength + format.axisThicknessPx() == grAxis.sizeYPx());
}