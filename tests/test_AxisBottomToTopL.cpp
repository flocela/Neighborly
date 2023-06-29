#include "catch.hpp"
#include "../src/AxisBottomToTopL.h"

TEST_CASE("AxisBottomToTopL.getPixel()_OddTickThickness_OddPixelsPerUnit")
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
    // Note pixel zero represents all values from [4.9, 5.1).
    //REQUIRE( 31 == axis.getAxisLengthPx()); //31
    REQUIRE( pair<int, int>{5, 5} == axis.getPixel(4, 1) ); // {5, 5}
    //REQUIRE( pair<int, int>{7, 7} == axis.getPixel(3.5, 1) ); // {7, 7}
    //REQUIRE( pair<int, int>{6, 6} == axis.getPixel(3.75, 1) ); // {6, 6}
    //REQUIRE( pair<int, int>{5, 5} == axis.getPixel(3.9, 1) );  // {5, 5}
    //REQUIRE( pair<int, int>{4, 5} == axis.getPixel(4, 2) ); //{4, 5}

}

/*
TEST_CASE("AxisBottomToTopL.getPixel()_OddTickThickness_EvenPixelsPerUnit")
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
    // Note, pixel zero represents values from [4.9375, 5.0625)
    REQUIRE( 51 == axis.getAxisLengthPx() ); // 50. Should be 51 ([-1 to 49]), but smallest pixel is 0
    REQUIRE( pair<int, int>{7, 9} == axis.getPixel(4, 3) ); // {7, 9}
    REQUIRE( pair<int, int>{11, 13} == axis.getPixel(3.5, 3) ); // {11, 13}
    REQUIRE( pair<int, int>{12, 14} == axis.getPixel(3.4, 3) ); // {12, 14}
    REQUIRE( pair<int, int>{22, 24} == axis.getPixel(2.0625, 3) ); // {22, 24}
    REQUIRE( pair<int, int>{23, 25} == axis.getPixel(1.9375, 3) ); // {23, 25}
    REQUIRE( pair<int, int>{30, 33} = axis.getPixel(1, 4)); // {30, 33}
    REQUIRE( pair<int, int>{35, 38} == axis.getPixel(.4375, 4)); // {35, 38}
}


TEST_CASE("AxisBottomToTopL.getPixel()_EvenTickThickness_OddPixelsPerUnit")
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
        2, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    // value 5 is represented between pixels 0 and 1
    // value 4 is represented between pixels 5 and 6
    // value 3 is represented between pixels 10 and 11
    // value 2 is represented between pixels 15 and 16
    // value 1 is represented between pixels 20 and 21
    // value 0 is represented between pixels 25 and 26
    // value -1 is represented between pixels 30 and 31
    // Note, pixel zero represents values from [5.0, 5.2)
    REQUIRE( 32 == axis.getAxisLengthPx() );//32
    REQUIRE( pair<int, int>{5, 6} == axis.getPixel(4, 2) );// {5, 6}
    REQUIRE( pair<int, int>{7, 8} == axis.getPixel(3.5, 2) );// {7, 8}
    REQUIRE( pair<int, int>{18, 19} == axis.getPixel(1.3, 2) );// {18, 19}
    REQUIRE( pair<int, int>{14, 15} == axis.getPixel(2.2, 2) );// {14, 15}
    REQUIRE( pair<int, int>{5, 7} = axis.getPixel(2.0, 3)); // {5, 6, 7}
}

TEST_CASE("AxisBottomToTopL.getPixel()_EvenTickThickness_EvenPixelsPerUnit")
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
        4, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    // value 5 is represented between pixels 0 and 1
    // value 4 is represented between pixels 8 and 9
    // value 3 is represented between pixels 16 and 17
    // value 2 is represented between pixels 24 and 25
    // value 1 is represented between pixels 32 and 33
    // value 0 is represented between pixels 40 and 41
    // value -1 is represented between pixels 48 and 49
    // Note, pixel zero represents values from [5.0, 5.125)
    REQUIRE( 51 == axis.getAxisLengthPx() ); //51, should be 52, but smallest pixel is 0
    REQUIRE( pair<int, int>{7, 10} == axis.getPixel(4, 4) ); // {7, 10}
    REQUIRE( pair<int, int>{19, 22} == axis.getPixel(2.5, 4) ); //{19, 22}
    REQUIRE( pair<int, int>{12, 15} == axis.getPixel(3.4, 4) ); //{12, 15}
    REQUIRE( pair<int, int>{27, 30} == axis.getPixel(1.4375, 4) ); //{27, 30}
    REQUIRE( pair<int, int>{31, 33} = axis.getPixel(1.0, 3)); 
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
        format.majTickLengthOutsideChartPx() +
        format.axisThicknessPx();

    REQUIRE ( labelLength == axis.getLabelLengthPx() );
}
*/