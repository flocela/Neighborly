#include "catch.hpp"
#include "../src/ForwardAxis.h"

using namespace std;

TEST_CASE("ForwardAxis.getPixel()_Cross_Centered_On_Pixel")
{
    ForwardAxis axis {
        0, // coordinate where axis and cross axis meet
        true,
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        1, // tickThickness
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
    
    REQUIRE( 31 == axis.getAxisLengthPx() );//31
    REQUIRE( pair<int, int>{25, 25} == axis.getPixel(4, 1) ); // {25, 25}
    REQUIRE( pair<int, int>{12, 12} == axis.getPixel(1.3, 1) ); // {12, 12}
    REQUIRE( pair<int, int>{16, 16} == axis.getPixel(2.2, 1) ); // {16, 16}
    REQUIRE( pair<int, int>{13, 14} == axis.getPixel(1.7, 2) ); // {13, 14} 
    REQUIRE( pair<int, int>{16, 17} == axis.getPixel(2.2, 2) ); // {16, 17}
}


TEST_CASE("ForwardAxis.getPixel()_Cross_Centered_On_Pixel_Diff_Dot_Sizes")
{
    ForwardAxis axis {
        0, // coordinate where axis and cross axis meet
        true,
        0, // minVal
        4, // maxVal
        5, // pxPerUnit
        3, // tickThickness
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
    
    REQUIRE( 33 == axis.getAxisLengthPx() );//33
    REQUIRE( pair<int, int>{24, 26} == axis.getPixel(4, 3) ); // {24, 26}
    REQUIRE( pair<int, int>{11, 13} == axis.getPixel(1.3, 3) ); // {11, 13}
    REQUIRE( pair<int, int>{15, 17} == axis.getPixel(2.2, 3) ); // {15, 17}
    REQUIRE( pair<int, int>{12, 15} == axis.getPixel(1.7, 4) ); // {12, 15}
    REQUIRE( pair<int, int>{15, 18} == axis.getPixel(2.2, 4) ); // {15, 18}
}

TEST_CASE("ForwardAxis.getPixel()_Cross_Between_Two_Pixels")
{
    ForwardAxis axis {
        0, // coordinate where axis and cross axis meet
        false,
        0, // minVal
        4, // maxVal 
        8, // pxPerUnit
        2, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // value -1 is represented by pixels 0 and 1
    // value 0 is represented by pixels 8 and 9
    // value 1 is represented by pixels 16 and 17
    // value 2 is represented by pixels 24 and 25
    // value 3 is represented by pixels 32 and 33
    // value 4 is represented by pixels 40 and 41
    // value 5 is represented by pixels 48 and 49
    // pixel 0 represents values [-1.125, 0)

    REQUIRE( 50 == axis.getAxisLengthPx() ); //50
    REQUIRE( pair<int,int>{15, 16} == axis.getPixel(1, 2) ); // {15, 16}
    REQUIRE( pair<int,int>{39, 40} == axis.getPixel(4, 2) ); // {39, 40}
    REQUIRE( pair<int,int>{35, 36} == axis.getPixel(3.5, 2) ); // {35, 36}
    REQUIRE( pair<int,int>{36, 37} == axis.getPixel(3.5625, 2) ); // {36, 37}
    REQUIRE( pair<int,int>{36, 36} == axis.getPixel(3.5, 1) ); // {36, 36}
    REQUIRE( pair<int,int>{35, 35} == axis.getPixel(3.4375, 1) ); // {35, 35}
}

TEST_CASE("ForwardAxis.getPixel()_Cross_Between_Two_Pixels_Diff_Dot_Sizes")
{
    ForwardAxis axis {
        0, // coordinate where axis and cross axis meet
        false,
        0, // minVal
        4, // maxVal 
        8, // pxPerUnit
        4, // tickThickness
        1, // start offset multiplier
        1  // end offset multplier
    };
    
    // value -1 is represented by pixels 0 and 1
    // value 0 is represented by pixels 8 and 9
    // value 1 is represented by pixels 16 and 17
    // value 2 is represented by pixels 24 and 25
    // value 3 is represented by pixels 32 and 33
    // value 4 is represented by pixels 40 and 41
    // value 5 is represented by pixels 48 and 49
    // pixel 0 represents values [-1.125, 0)

    REQUIRE( 52 == axis.getAxisLengthPx() ); //52
    REQUIRE( pair<int,int>{14, 17} == axis.getPixel(1, 4) ); // {14, 17}
    REQUIRE( pair<int,int>{38, 41} == axis.getPixel(4, 4) ); // {38, 41}
    REQUIRE( pair<int,int>{34, 37} == axis.getPixel(3.5, 4) ); // {34, 37}
    REQUIRE( pair<int,int>{35, 38} == axis.getPixel(3.5625, 4) ); // {35, 38}
    REQUIRE( pair<int,int>{35, 37} == axis.getPixel(3.5, 3) ); // {35, 37}
    REQUIRE( pair<int,int>{34, 36} == axis.getPixel(3.4375, 3) ); // {34, 36}
}
