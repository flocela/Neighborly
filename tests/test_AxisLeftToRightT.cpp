#include "catch.hpp"
#include "../src/AxisLeftToRightT.h"

TEST_CASE("AxisLeftToRightT.getPixel()_OddTickThickness_OddPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightT axis {
        format,
        0, // x coord where x and y axes meet
        0, // y coord where x and y axes meet
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // tick pixel is at 0  representing value -1
    // tick pixel is at 5  representing value  0
    // tick pixel is at 10 representing value  1
    // tick pixel is at 15 representing value  2
    // tick pixel is at 20 representing value  3
    // tick pixel is at 25 representing value  4
    // tick pixel is at 30 representing value  5
    
    REQUIRE( 31 == axis.getAxisLengthPx() );//31
    REQUIRE( 25 == axis.getPixel(4) );// 25
    REQUIRE( 23 == axis.getPixel(3.5) );// 23
    REQUIRE( 12 == axis.getPixel(1.3) );// 12
    REQUIRE( 16 == axis.getPixel(2.2) );// 16
}

TEST_CASE("AxisLeftToRightT.getPixel()_OddTickThickness_EvenPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightT axis {
        format,
        0, // x coord where x and y axes meet
        0, // y coord where x and y axes meet
        0, // minVal
        4, // maxVal
        8, // pxPerUnit
        3, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // tick pixel is at 0  representing value -1; tick is at pixels: -1,  0, 1
    // tick pixel is at 8  representing value  0; tick is at pixels:  7,  8, 9
    // tick pixel is at 16 representing value  1; tick is at pixels: 15, 16, 17
    // tick pixel is at 24 representing value  2; tick is at pixels: 23, 24, 25
    // tick pixel is at 32 representing value  3; tick is at pixels: 31, 32, 33
    // tick pixel is at 40 representing value  4; tick is at pixels: 39, 40, 41
    // tick pixel is at 48 representing value  5; tick is at pixels: 47, 48, 49
    REQUIRE( 51 == axis.getAxisLengthPx() );//51
    REQUIRE( 16 == axis.getPixel(1) ); //16
    REQUIRE( 40 == axis.getPixel(4) ); //40
    REQUIRE( 36 == axis.getPixel(3.5) ); //36
    REQUIRE( 37 == axis.getPixel(3.6) ); //37
}

TEST_CASE("AxisLeftToRightT.getPixel()_EvenTickThickness_OddPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightT axis {
        format,
        0, // x coord where x and y axes meet
        0, // y coord where x and y axes meet
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        2, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // tick pixel is at 0  representing value -1; tick pixels at -1 and  0
    // tick pixel is at 5  representing value  0; tick pixels at  4 and  5
    // tick pixel is at 10 representing value  1; tick pixels at  9 and 10
    // tick pixel is at 15 representing value  2; tick pixels at 14 and 15
    // tick pixel is at 20 representing value  3; tick pixels at 19 and 20
    // tick pixel is at 25 representing value  4; tick pixels at 24 and 25
    // tick pixel is at 30 representing value  5; tick pixels at 29 and 30
    REQUIRE( 32 == axis.getAxisLengthPx() );//32
    REQUIRE( 25 == axis.getPixel(4) );// 25
    REQUIRE( 23 == axis.getPixel(3.5) );// 23
    REQUIRE( 12 == axis.getPixel(1.3) );// 12
    REQUIRE( 16 == axis.getPixel(2.2) );// 16
}

TEST_CASE("AxisLeftToRightT.getPixel()_EvenTickThickness_EvenPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightT axis {
        format,
        0, // x coord where x and y axes meet
        0, // y coord where x and y axes meet
        0, // minVal
        4, // maxVal
        8, // pxPerUnit
        4, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // tick pixel is at 0  representing value -1; tick pixels at -2, -1,  0,  1
    // tick pixel is at 8  representing value  0; tick pixels at  6,  7,  8,  9
    // tick pixel is at 16 representing value  1; tick pixels at 14, 15, 16, 17
    // tick pixel is at 24 representing value  2
    // tick pixel is at 32 representing value  3
    // tick pixel is at 40 representing value  4
    // tick pixel is at 48 representing value  5; tick pixels at 46, 47, 48, 49
    REQUIRE( 52 == axis.getAxisLengthPx() ); //52
    REQUIRE( 16 == axis.getPixel(1) ); //16
    REQUIRE( 40 == axis.getPixel(4) ); //40
    REQUIRE( 36 == axis.getPixel(3.5) ); //36
    REQUIRE( 37 == axis.getPixel(3.6) ); //37
}