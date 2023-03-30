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
    
    // tick pixel is at 0  representing value 5
    // tick pixel is at 5  representing value 4
    // tick pixel is at 10 representing value 3
    // tick pixel is at 15 representing value  2
    // tick pixel is at 20 representing value  1
    // tick pixel is at 25 representing value  0
    // tick pixel is at 30 representing value -1
    // Note pixel 0 represents all values from 4.9 inclusive, to 5.1 exclusive.
    REQUIRE( 31 == axis.getAxisLengthPx()); //31
    REQUIRE(  5 == axis.getPixel(4) ); //5
    REQUIRE(  7 == axis.getPixel(3.5) ); //7
    REQUIRE(  7 == axis.getPixel(3.55) ); //7
    REQUIRE(  6 == axis.getPixel(3.75) ); //6
    REQUIRE(  5 == axis.getPixel(3.9) );  //5
}

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
    // tick pixel is at 0  representing value 5
    // tick pixel is at 8  representing value 4
    // tick pixel is at 16 representing value 3
    // tick pixel is at 24 representing value  2
    // tick pixel is at 32 representing value  1
    // tick pixel is at 40 representing value  0
    // tick pixel is at 48 representing value -1 
    REQUIRE( 51 == axis.getAxisLengthPx() ); //51
    REQUIRE(  8 == axis.getPixel(4) ); //8
    REQUIRE( 12 == axis.getPixel(3.5) ); //12
    REQUIRE( 13 == axis.getPixel(3.4) ); //13
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
    // tick pixel is at 1  representing value 5;  tick is at pixels: 0 and 1
    // tick pixel is at 6  representing value 4;  tick is at pixels: 5 and 6
    // tick pixel is at 11 representing value 3;  tick is at pixels: 10 and 11
    // tick pixel is at 16 representing value  2; tick is at pixels: 15 and 16
    // tick pixel is at 21 representing value  1; tick is at piexls: 20 and 21
    // tick pixel is at 26 representing value  0; tick is at pixels: 25 and 26
    // tick pixel is at 31 representing value -1; tick is at pixels: 30 and 31

    REQUIRE( 32 == axis.getAxisLengthPx() );//32
    REQUIRE(  6 == axis.getPixel(4) );// 6
    REQUIRE(  8 == axis.getPixel(3.5) );// 8
    REQUIRE( 19 == axis.getPixel(1.3) );// 19
    REQUIRE( 15 == axis.getPixel(2.2) );// 15
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
    // tick pixel is at 1  representing value  5; tick is at pixels: 0 and 1
    // tick pixel is at 9  representing value  4; tick is at pixels: 8 and 9
    // tick pixel is at 17 representing value  3; tick is at pixels: 16 and 17
    // tick pixel is at 25 representing value  2; tick is at pixels: 24 and 25
    // tick pixel is at 33 representing value  1; tick is at pixels: 32 and 33
    // tick pixel is at 41 representing value  0; tick is at pixels: 40 and 41
    // tick pixel is at 49 representing value -1; tick is at pixels: 48 and 49
    REQUIRE( 52 == axis.getAxisLengthPx() ); //52
    REQUIRE(  9 == axis.getPixel(4) ); //9
    REQUIRE( 21 == axis.getPixel(2.5) ); //21
    REQUIRE( 14 == axis.getPixel(3.4) ); //14
}