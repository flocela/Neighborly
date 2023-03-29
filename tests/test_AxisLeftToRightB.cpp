#include "catch.hpp"
#include "../src/AxisLeftToRightB.h"

TEST_CASE("AxisLeftToRightB.getPixel()WithOddTickThicknessAndOddPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightB axis {
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

TEST_CASE("AxisLeftToRightB.getPixel()WithOddTickThicknessAndEvenPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightB axis {
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
    
    // tick pixel is at 0  representing value -1
    // tick pixel is at 8  representing value  0
    // tick pixel is at 16 representing value  1
    // tick pixel is at 24 representing value  2
    // tick pixel is at 32 representing value  3
    // tick pixel is at 40 representing value  4
    // tick pixel is at 48 representing value  5 
    REQUIRE( 51 == axis.getAxisLengthPx() );
    REQUIRE( 16 == axis.getPixel(1) );
    REQUIRE( 40 == axis.getPixel(4) );
    REQUIRE( 36 == axis.getPixel(3.5) );
    REQUIRE( 37 == axis.getPixel(3.6) );
}

TEST_CASE("AxisLeftToRightB.getPixel()WithEvenTickThicknessAndOddPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightB axis {
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
    
    // tick pixel is at 0  representing value -1
    // tick pixel is at 5  representing value  0
    // tick pixel is at 10 representing value  1
    // tick pixel is at 15 representing value  2
    // tick pixel is at 20 representing value  3
    // tick pixel is at 25 representing value  4
    // tick pixel is at 30 representing value  5 
    REQUIRE( 32 == axis.getAxisLengthPx() );//32
    REQUIRE( 25 == axis.getPixel(4) );// 25
    REQUIRE( 23 == axis.getPixel(3.5) );// 23
    REQUIRE( 12 == axis.getPixel(1.3) );// 12
    REQUIRE( 16 == axis.getPixel(2.2) );// 16
}

TEST_CASE("AxisLeftToRightB.getPixel()WithEvenTickThicknessAndEvenPixelsPerUnit")
{
    AxisFormat format{};
    AxisLeftToRightB axis {
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
    
    // tick pixel is at 0  representing value -1
    // tick pixel is at 8  representing value  0
    // tick pixel is at 16 representing value  1
    // tick pixel is at 24 representing value  2
    // tick pixel is at 32 representing value  3
    // tick pixel is at 40 representing value  4
    // tick pixel is at 48 representing value  5 
    REQUIRE( 52 == axis.getAxisLengthPx() );
    REQUIRE( 16 == axis.getPixel(1) );
    REQUIRE( 40 == axis.getPixel(4) );
    REQUIRE( 36 == axis.getPixel(3.5) );
    REQUIRE( 37 == axis.getPixel(3.6) );
}