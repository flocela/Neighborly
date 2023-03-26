#include "catch.hpp"
#include "../src/AxisBottomToTopL.h"

TEST_CASE("AxisBottomToTopL.getPixel()WithOddPixelsPerUnit")
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
    REQUIRE(31 == axis.getAxisLengthPx());
    REQUIRE( 5 == axis.getPixel(4) );
    REQUIRE( 7 == axis.getPixel(3.5) );
    REQUIRE( 7 == axis.getPixel(3.55) );
    REQUIRE( 6 == axis.getPixel(3.75) );
    REQUIRE( 5 == axis.getPixel(3.9) );
}

TEST_CASE("AxisBottomToTopL.getPixel()WithEvenPixelsPerUnit")
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
        2, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    // This example is for an even px per unit. The tick is two 
    // pixels in length. The top tick pixel is listed below.
    // But realize, the pixel given by getPixel() is one pixel
    // below the top tick pixel. So that when printing the tick,
    // the user will subtract 1/2 tick width from given pixel,
    // and that would be the top of the tick.
    // In this example. getAxisLengthPx(5) should result in pixel 1.
    // Then the top of the tick (for a 2 px per unit tick) is at 0.
    // tick pixel is at 0  representing value 5
    // tick pixel is at 8  representing value 4
    // tick pixel is at 16 representing value 3
    // tick pixel is at 24 representing value  2
    // tick pixel is at 32 representing value  1
    // tick pixel is at 40 representing value  0
    // tick pixel is at 48 representing value -1 
    REQUIRE( 50 == axis.getAxisLengthPx() );
    REQUIRE(  9 == axis.getPixel(4) );
    REQUIRE( 13 == axis.getPixel(3.5) );
    REQUIRE( 14 == axis.getPixel(3.4) );
}