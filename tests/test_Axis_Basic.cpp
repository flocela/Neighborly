#include "catch.hpp"

#include "../src/Axis_Basic.h"

using namespace std;

TEST_CASE("Axis_Basic::forward is false, using dot sizes of 1 and 2")
{
    Axis_Basic axis {
        false,
        30, // largest pixel on axis
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // value -1 represented by pixel 30
    // value 0 represented by pixel 25
    // value 1 represented by pixel 20
    // value 2 represented by pixel 15
    // value 3 represented by pixel 10
    // value 4 represented by pixel 5
    // value 5 represented by pixel 0
    // pixel 0 represent values (4.9, 5.1]
    
    REQUIRE(0 == axis.getStartPixel()); // 0
    REQUIRE(30 == axis.getEndPixel()); // 30
    REQUIRE( pair<int, int>{5, 5} == axis.getPixels(4, 1) ); // {5, 5}
    REQUIRE( pair<int, int>{19, 19} == axis.getPixels(1.3, 1) ); // {19, 19}
    REQUIRE( pair<int, int>{14, 14} == axis.getPixels(2.2, 1) ); // {14, 14}
    REQUIRE( pair<int, int>{16, 17} == axis.getPixels(1.7, 2) ); // {16, 17} 
    REQUIRE( pair<int, int>{14, 15} == axis.getPixels(2.2, 2) ); // {14, 15}
    
}

TEST_CASE("Axis_Basic::forward is false, using dot sizes of 3 and 4")
{
    Axis_Basic axis {
        false,
        30, // largest pixel on axis
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // start offset multiplier
        1  // end offset multplier
    };

    // value -1 represented by pixel 30
    // value 0 represented by pixel 25
    // value 1 represented by pixel 20
    // value 2 represented by pixel 15
    // value 3 represented by pixel 10
    // value 4 represented by pixel 5
    // value 5 represented by pixel 0
    // pixel 0 represent values (4.9, 5.1]
    
    REQUIRE(0 == axis.getStartPixel()); // 0
    REQUIRE(30 == axis.getEndPixel()); // 30
    REQUIRE( 31 == axis.getAxisLengthPx() );//31
    REQUIRE( pair<int, int>{4, 6} == axis.getPixels(4, 3) ); // {4, 6}
    REQUIRE( pair<int, int>{18, 20} == axis.getPixels(1.3, 3) ); // {18, 20}
    REQUIRE( pair<int, int>{13, 15} == axis.getPixels(2.2, 3) ); // {13, 15}
    REQUIRE( pair<int, int>{15, 18} == axis.getPixels(1.7, 4) ); // {15, 18}
    REQUIRE( pair<int, int>{13, 16} == axis.getPixels(2.2, 4) ); // {13, 16}
}

TEST_CASE("Axis_Basic::forward is true, using dot sizes of 1 and 2")
{
    Axis_Basic axis {
        true,
        0, // smallest pixel on axis
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // value -1 represented by pixel 0
    // value 0 represented by pixel 5
    // value 1 represented by pixel 10
    // value 2 represented by pixel 15
    // value 3 represented by pixel 20
    // value 4 represented by pixel 25
    // value 5 represented by pixel 30
    // pixel 0 represent values (-.9, -1.1]
    
    REQUIRE(0 == axis.getStartPixel()); // 0
    REQUIRE(30 == axis.getEndPixel()); // 30
    REQUIRE( 31 == axis.getAxisLengthPx() );//31
    REQUIRE( pair<int, int>{25, 25} == axis.getPixels(4, 1) ); // {25, 25}
    REQUIRE( pair<int, int>{12, 12} == axis.getPixels(1.3, 1) ); // {12, 12}
    REQUIRE( pair<int, int>{16, 16} == axis.getPixels(2.2, 1) ); // {16, 16}
    REQUIRE( pair<int, int>{13, 14} == axis.getPixels(1.7, 2) ); // {13, 14} 
    REQUIRE( pair<int, int>{16, 17} == axis.getPixels(2.2, 2) ); // {16, 17}
}

TEST_CASE("Axis_Basic::forward is true, using dot sizes of 3 and 4")
{
    Axis_Basic axis {
        true,
        0, // smallest pixel on axis
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // start offset multiplier
        1  // end offset multplier
    };

    // value -1 represented by pixel 0
    // value 0 represented by pixel 5
    // value 1 represented by pixel 10
    // value 2 represented by pixel 15
    // value 3 represented by pixel 20
    // value 4 represented by pixel 25
    // value 5 represented by pixel 30
    // pixel 0 represent values (-.9, -1.1]
    
    REQUIRE(0 == axis.getStartPixel()); // 0
    REQUIRE(30 == axis.getEndPixel()); // 30
    REQUIRE( 31 == axis.getAxisLengthPx() );//31
    REQUIRE( pair<int, int>{24, 26} == axis.getPixels(4, 3) ); // {24, 26}
    REQUIRE( pair<int, int>{11, 13} == axis.getPixels(1.3, 3) ); // {11, 13}
    REQUIRE( pair<int, int>{15, 17} == axis.getPixels(2.2, 3) ); // {15, 17}
    REQUIRE( pair<int, int>{12, 15} == axis.getPixels(1.7, 4) ); // {12, 15}
    REQUIRE( pair<int, int>{15, 18} == axis.getPixels(2.2, 4) ); // {15, 18}
}