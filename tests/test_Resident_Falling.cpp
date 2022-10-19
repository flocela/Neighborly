#include "catch.hpp"
#include "../src/Resident_Falling.h"
#include "../src/Resident_Flat.h"
#include "../src/House.h"
#include <set>
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor001{1, 1, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor002{2, 1, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor003{3, 1, 0.0, 0.0, 0.0 };
    
Resident_Flat greenNeighbor001{1, 2, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor002{2, 2, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor003{3, 2, 0.0, 0.0, 0.0 };

TEST_CASE("Resident_Falling Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            -0.25, // happiness goal
            1.0,
            0.2,
            0.1
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
} 

TEST_CASE("Resident_Falling Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0, 
            1.2, // happiness goal
            1.0,
            0.2, 
            0.1 
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );

}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            -0.3, // value at zero Diversity
            0.1
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            1.2, // value at zero Diversity
            0.1
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at one is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            0.2,
            -0.3 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            0.2,
            1.2 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Falling Ctor throws exception if"
" happinessValueAtZeroDiversity is smaller than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            .25, // value at zero Diversity
            .75  // value at one Diversity
        ), 
        Contains("happinessAtZeroDiversity must be"
        " larger than happinessAtOneDiversity.") );
}

TEST_CASE("Resident_Falling Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Falling(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            .75,
            .75
        ), 
        Contains("happinessAtZeroDiversity must be"
        " larger than happinessAtOneDiversity.")
    );
}

TEST_CASE("getHappiness()")
{
    Resident_Falling greenResident{ 
        0, 
        2, 
        0.0,  
        0.0, 
        1.0,
        0.8, // happinessValueAtZeroDiversity
        0.2, // happinessValueAtOneDiversity
    };

    std::set<Resident*> neighbors = { 
        &greenNeighbor001,
        &greenNeighbor002,
        &greenNeighbor003,
        &blueNeighbor001
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.65);
}

TEST_CASE("Resident_Falling toStrBasic()")
{
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  
        0.25, 
        1.0,
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_Falling(id, clr, mov, goal, hap0, hap1):"
        " (1, green_neutral, 0.000000, 0.250000, 0.750000, 0.250000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

const House h0 = House{0};
const House h1 = House{1};
const House h2 = House{2};
const House h3 = House{3};
const House h4 = House{4};
const House h5 = House{5};
const House h6 = House{6};
const House h7 = House{7};
const House h8 = House{8};
const House h9 = House{9};
const House h10 = House{10};
const House h11 = House{11};
const House h12 = House{12};
const House h13 = House{13};
const House h14 = House{14};
const House h15 = House{15};
const House h16 = House{16};
const House h17 = House{17};
const House h18 = House{18};
const House h19 = House{19};
const House h20 = House{20};
const House h21 = House{21};
const House h22 = House{22};
const House h23 = House{23};
const House h24 = House{24};

TEST_CASE("Resident_Falling findHome()"
    " green_neutral resident has choice of one green_neutral neigbor or one blue_neutral neigbor,"
    " chooses green_neutral neighbor")
{
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        1.0,
        0.5,  // happinessValueAtZeroDiversity
        0.1,  // happinessValueAtOneDiversity
    };

    const House& oldHouse = h0; // resident's current house
    const House& grHouse8 = h8;  // green_neutral resident lives in house 8
    const House& blHouse16 = h16; // blue_neutral resident lives in house 16
    const House& house11  = h11; // next to blue_neutral resident
    const House& house13  = h13; // next to green_neutral resident

    std::set<const House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&h7);
    housesAdjToHouse13.insert(&h8);
    housesAdjToHouse13.insert(&h9);
    housesAdjToHouse13.insert(&h12);
    housesAdjToHouse13.insert(&h14);
    housesAdjToHouse13.insert(&h17);
    housesAdjToHouse13.insert(&h18);
    housesAdjToHouse13.insert(&h19);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h5);
    housesAdjToHouse11.insert(&h6);
    housesAdjToHouse11.insert(&h7);
    housesAdjToHouse11.insert(&h10);
    housesAdjToHouse11.insert(&h12);
    housesAdjToHouse11.insert(&h15);
    housesAdjToHouse11.insert(&h16);
    housesAdjToHouse11.insert(&h17);

    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjHouses;
    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &h13,
        housesAdjToHouse13
        )
    );
    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &h11,
        housesAdjToHouse11)
    );

    std::unordered_map<const House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&greenNeighbor001));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blueNeighbor001));
    REQUIRE(
        greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        ) ==
        &h13
    );

}

TEST_CASE("Resident_Falling findHome()"
    " green_neutral resident has choice of a) two green_neutral neigbors, b) two green_neutral + 1 blue_neutral neighbors,"
    " or c) one blue_neutral plus one green_neutral neigbor, chooses either a) or b).")
{ 
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.6,  // happiness Goal
        1.0,
        1.0,  // happinessValueAtZeroDiversity
        0.0,  // happinessValueAtOneDiversity
    };

    const House& oldHouse  = h0;  // resident's current house
    const House& grHouse7  = h7;  // green_neutral resident lives in house 7
    const House& grHouse8  = h8;  // green_neutral resident lives in house 8
    const House& blHouse16 = h16; // blue_neutral resident lives in house 16
    const House& house2  = h2;  // next to two green_neutral residents (happiness = 1.0)
    const House& house11 = h11; // next to one blue_neutral resident + one green_neutral resident (happiness = 0.5)
    const House& house12 = h12; // next to two green_neutral + one blue_neutral residents (happiness = 0.66)

    std::set<const House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h1);
    housesAdjToHouse2.insert(&h3);
    housesAdjToHouse2.insert(&h6);
    housesAdjToHouse2.insert(&h7);
    housesAdjToHouse2.insert(&h8);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h5);
    housesAdjToHouse11.insert(&h6);
    housesAdjToHouse11.insert(&h7);
    housesAdjToHouse11.insert(&h10);
    housesAdjToHouse11.insert(&h12);
    housesAdjToHouse11.insert(&h15);
    housesAdjToHouse11.insert(&h16);
    housesAdjToHouse11.insert(&h17);

    std::set<const  House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h6);
    housesAdjToHouse12.insert(&h7);
    housesAdjToHouse12.insert(&h8);
    housesAdjToHouse12.insert(&h11);
    housesAdjToHouse12.insert(&h13);
    housesAdjToHouse12.insert(&h16);
    housesAdjToHouse12.insert(&h17);
    housesAdjToHouse12.insert(&h18);

    std::map<const House*, std::set<const  House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house11,
        housesAdjToHouse11)
    );

    std::unordered_map<const House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse7,&greenNeighbor001));
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&greenNeighbor002));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blueNeighbor001));
    
    const House* answerHouse = greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE( (answerHouse == &house12 || answerHouse == &house2) );

}

TEST_CASE("Resident_Falling findBestHome()"
    " green_neutral resident has choice of a) two green_neutral neigbors, b) two green_neutral + 1 blue_neutral neighbors,"
    " or c) one blue_neutral plus one green_neutral neigbor, chooses a).")
{  
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.6,  // happiness Goal
        1.0,
        1.0,  // happinessValueAtZeroDiversity
        0.0,  // happinessValueAtOneDiversity
    };

    const House& oldHouse = h0;  // resident's current house
    const House& grHouse7 = h7;  // green_neutral resident lives in house 7
    const House& grHouse8 = h8;  // green_neutral resident lives in house 8
    const House& blHouse16 = h16; // blue_neutral resident lives in house 16
    const House& house2    = h2;  // next to two green_neutral residents (happiness = 1.0)
    const House& house11   = h11; // next to one blue_neutral resident + one green_neutral resident (happiness = 0.5)
    const House& house12   = h12; // next to two green_neutral + one blue_neutral residents (happiness = 0.66)

    std::set<const House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h1);
    housesAdjToHouse2.insert(&h3);
    housesAdjToHouse2.insert(&h6);
    housesAdjToHouse2.insert(&h7);
    housesAdjToHouse2.insert(&h8);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h5);
    housesAdjToHouse11.insert(&h6);
    housesAdjToHouse11.insert(&h7);
    housesAdjToHouse11.insert(&h10);
    housesAdjToHouse11.insert(&h12);
    housesAdjToHouse11.insert(&h15);
    housesAdjToHouse11.insert(&h16);
    housesAdjToHouse11.insert(&h17);

    std::set<const House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h6);
    housesAdjToHouse12.insert(&h7);
    housesAdjToHouse12.insert(&h8);
    housesAdjToHouse12.insert(&h11);
    housesAdjToHouse12.insert(&h13);
    housesAdjToHouse12.insert(&h16);
    housesAdjToHouse12.insert(&h17);
    housesAdjToHouse12.insert(&h18);

    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house11,
        housesAdjToHouse11)
    );

    std::unordered_map<const House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse7,&greenNeighbor001));
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&greenNeighbor002));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blueNeighbor001));
    
    const House* answerHouse = greenResident.findBestHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE( answerHouse == &house2 );

}