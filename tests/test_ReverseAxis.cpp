#include "catch.hpp"
#include "../src/ReverseAxis.h"
#include <iostream>
using namespace std;

TEST_CASE("ReverseAxis().getPixels_Cross_Centered_On_Pixel")
{
    ReverseAxis axis {
        30, // coordinate where axis and cross axis meet
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // tickThickness
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
    
    REQUIRE( 31 == axis.getAxisLengthPx() );//31
    REQUIRE( pair<int, int>{5, 5} == axis.getPixels(4, 1) ); // {5, 5}
    REQUIRE( pair<int, int>{19, 19} == axis.getPixels(1.3, 1) ); // {19, 19}
    REQUIRE( pair<int, int>{14, 14} == axis.getPixels(2.2, 1) ); // {14, 14}
    REQUIRE( pair<int, int>{16, 17} == axis.getPixels(1.7, 2) ); // {16, 17} 
    REQUIRE( pair<int, int>{14, 15} == axis.getPixels(2.2, 2) ); // {14, 15}
}


TEST_CASE("ReverseAxis.getPixels()_Cross_Centered_On_Pixel_Diff_Dot_Sizes")
{
    ReverseAxis axis {
        30, // coordinate where axis and cross axis meet
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        3, // tickThickness
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
    
    REQUIRE( 33 == axis.getAxisLengthPx() );//33
    REQUIRE( pair<int, int>{4, 6} == axis.getPixels(4, 3) ); // {4, 6}
    REQUIRE( pair<int, int>{18, 20} == axis.getPixels(1.3, 3) ); // {18, 20}
    REQUIRE( pair<int, int>{13, 15} == axis.getPixels(2.2, 3) ); // {13, 15}
    REQUIRE( pair<int, int>{15, 18} == axis.getPixels(1.7, 4) ); // {15, 18}
    REQUIRE( pair<int, int>{13, 16} == axis.getPixels(2.2, 4) ); // {13, 16}
}