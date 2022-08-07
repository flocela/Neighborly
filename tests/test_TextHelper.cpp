#include "catch.hpp"
#include "../src/Resident_Flat.h"
#include "../src/City_Grid.h"
#include "../src/Resident_StepDown.h"
#include "../src/TextHelper.h"
#include "../src/House.h"
#include "../src/Resident.h"
#include <vector>
#include <map>
using Catch::Matchers::Contains;

Resident_StepDown blueNeighbor006{
    6,           // id
    1, // color
    0.0,         // movement
    0.25,        // happiness goal
    0.75,        // happiness at zero diversity
    0.25,        // happiness at one diversity
    0.5          // diversity where drop happens
};

Resident_StepDown blueNeighbor007{
    7,
    1,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor008{
    8,
    1,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor011{
    11,
    1,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor012{
    12,
    1,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor016{
    16,
    1,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown blueNeighbor018{
    18,
    1, 
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor013{
    13,
    3, 
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor014{
    14,
    3, 
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor017{
    17,
    3, 
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor019{
    19,
    3,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor022{
    22,
    3, 
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor023{
    23,
    3, 
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

Resident_StepDown redNeighbor024{
    24,
    3,
    0.0,  
    0.25, 
    0.75, 
    0.25, 
    0.5   
};

/*
    City is a 5 by 5 grid.
    0  5  10  15  20
    1  6  11  16  21
    2  7  12  17  22
    3  8  13  18  23
    4  9  14  19  24

    Residents in city. B is for blue_neutral. R is for red.
    The blue_neutral resident in house 18 has 1 blue_neutral neighbor and 
    7 red neighbors.
    The blue_neutral resident in house 12 has 6 blue_neutral neighbors and
    2 red neighbors.
    0  5  10  15  20
    1  B   B   B  21
    2  B   B   R   R
    3  B   R   B   R
    4  9   R   R   R

    All residents have a happiness goal of 0.25 and since their
    current happiness has not been calculated it is still zero.

    Graph of residents' happiness values.
    *     *     *     *     *
    *  0.75  0.75  0.25     *
    *  0.75  0.75  0.25  0.25
    *  0.25  0.25  0.25  0.75
    *     *  0.25  0.75  0.75

*/

TEST_CASE("TextHelper create text()")
{
    int run = 1;
    int maxNumOfRuns = 10;
    int cityWidth = 5;
    std::string title = "title";
    City_Grid city{cityWidth};
    std::vector<House*> houses = city.getHouses();
    std::map<House*, Resident*> residentPerHouse{  
        {houses[6], &blueNeighbor006},
        {houses[7], &blueNeighbor007},
        {houses[8], &blueNeighbor008},
        {houses[11], &blueNeighbor011},
        {houses[12], &blueNeighbor012},
        {houses[16], &blueNeighbor016},
        {houses[18], &blueNeighbor018},
        {houses[13], &redNeighbor013},
        {houses[14], &redNeighbor014},
        {houses[17], &redNeighbor017},
        {houses[19], &redNeighbor019},
        {houses[22], &redNeighbor022},
        {houses[23], &redNeighbor023},
        {houses[24], &redNeighbor024}
    };
    std::string text = "Run/FinalRun: 1 / 10\n";
    text.append("Resident presented as:\n");
    text.append("Resident ID, color, address, coordinate,"
        " happiness / happiness goal \n");
    text.append("  6,  blue_neutral,  6,   (1, 1), 0/0.25\n");
    text.append("  7,  blue_neutral,  7,   (1, 2), 0/0.25\n");
    text.append("  8,  blue_neutral,  8,   (1, 3), 0/0.25\n");
    text.append(" 11,  blue_neutral, 11,   (2, 1), 0/0.25\n");
    text.append(" 12,  blue_neutral, 12,   (2, 2), 0/0.25\n");
    text.append(" 13,   red, 13,   (2, 3), 0/0.25\n");
    text.append(" 14,   red, 14,   (2, 4), 0/0.25\n");
    text.append(" 16,  blue_neutral, 16,   (3, 1), 0/0.25\n");
    text.append(" 17,   red, 17,   (3, 2), 0/0.25\n");
    text.append(" 18,  blue_neutral, 18,   (3, 3), 0/0.25\n");
    text.append(" 19,   red, 19,   (3, 4), 0/0.25\n");
    text.append(" 22,   red, 22,   (4, 2), 0/0.25\n");
    text.append(" 23,   red, 23,   (4, 3), 0/0.25\n");
    text.append(" 24,   red, 24,   (4, 4), 0/0.25\n");
    TextHelper textHelper{maxNumOfRuns, &city};
    std::string result = textHelper.createText(residentPerHouse, run);
    REQUIRE(text == result);
}