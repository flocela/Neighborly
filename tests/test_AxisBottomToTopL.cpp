#include "catch.hpp"
#include "../src/AxisBottomToTopL.h"

using namespace std;
/*
TEST_CASE("AxisBottomToTopL.getPixel()_x-axisCenteredOnPixel")
{   
    AxisFormat format{};
    AxisBottomToTopL axis {
        format,
        1, // horiz length
        0, // x coord where x and y axes meet
        30, // y coord where x and y axes meet
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // value 5 is represented by pixel 0
    // value 4 is represented by pixel 5
    // value 3 is represented by pixel 10
    // value 2 is represented by pixel 15
    // value 1 is represented by pixel 20
    // value 0 is represented by pixel 25
    // value -1 is represented by pixel 30
    // Note pixel zero represents all values from (4.9, 5.1].
    REQUIRE( 31 == axis.getAxisLengthPx()); //31
    REQUIRE( pair<int, int>{5, 5} == axis.getPixels(4, 1) ); // {5, 5}
    REQUIRE( pair<int, int>{8, 8} == axis.getPixels(3.5, 1) ); // {8, 8}
    REQUIRE( pair<int, int>{6, 6} == axis.getPixels(3.75, 1) ); // {6, 6}
    REQUIRE( pair<int, int>{6, 6} == axis.getPixels(3.9, 1) );  // {6, 6}
    REQUIRE( pair<int, int>{5, 6} == axis.getPixels(4, 2) ); // {5, 6}
    REQUIRE( pair<int, int>{4, 5} == axis.getPixels(4.1, 2) ); // {5, 6}
}

// Use a dotSize which is not one. Also, getAxisLengthPx() should return
// 50 instead of 51. The axis gets cut off at the top because the pixels only go to 0,
// not -1.
TEST_CASE("AxisBottomToTopL.getPixels()_x-axisCenteredOnPixel_Diff_DotSizes")
{
    AxisFormat format{};
    AxisBottomToTopL axis {
        format,
        1, // horiz length
        0, // x coord where x and y axes meet
        48, // y coord where x and y axes meet
        0, // minVal
        4, // maxVal
        8, // pxPerUnit
        3, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    // value 5 is represented by pixel 0
    // value 4 is represented by pixel 8
    // value 3 is represented by pixel 16
    // value 2 is represented by pixel 24
    // value 1 is represented by pixel 32
    // value 0 is represented by pixel 40
    // value -1 is represented by pixel 48
    // Note, pixel zero represents values from (4.9375, 5.0625]

    REQUIRE( 51 == axis.getAxisLengthPx() ); 
    REQUIRE( pair<int, int>{7, 9} == axis.getPixels(4, 3) ); // {7, 9}
    REQUIRE( pair<int, int>{11, 13} == axis.getPixels(3.5, 3) ); // {11, 13}
    REQUIRE( pair<int, int>{12, 14} == axis.getPixels(3.4, 3) ); // {12, 14}
    REQUIRE( pair<int, int>{23, 25} == axis.getPixels(2.0625, 3) ); // {23, 24}
    REQUIRE( pair<int, int>{24, 26} == axis.getPixels(1.9375, 3) ); // {24, 25}
    REQUIRE( pair<int, int>{31, 34} == axis.getPixels(1, 4)); // {31, 34}
    REQUIRE( pair<int, int>{35, 38} == axis.getPixels(.4375, 4)); // {35, 38}
}


TEST_CASE("AxisBottomToTopL.getLabelLengthPx()")
{
   AxisFormat format{};
    AxisBottomToTopL axis {
        format,
        0, // horiz length
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
        format.majTickLengthOutsideChartPx();

    REQUIRE ( labelLength == axis.getLabelLengthPx() );
    REQUIRE ( labelLength + format.axisThicknessPx() == axis.sizeXPx());
}
*/