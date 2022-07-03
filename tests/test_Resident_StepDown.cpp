#include "catch.hpp"
#include "../src/Resident_StepDown.h"
#include "../src/Resident_Flat.h"
#include <set>
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor1{1, 1, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor2{2, 1, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor3{3, 1, 0.0, 0.0, 0.0 };
    
Resident_Flat greenNeighbor1{1, 2, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor2{2, 2, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor3{3, 2, 0.0, 0.0, 0.0 };
    

TEST_CASE("Resident_StepDown Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            1.2, //happinessGoal
            0.2, 
            0.1,
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            -0.1, //happinessGoal 
            0.2, 
            0.1,
            0.0 
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            -0.2, // happinessValueAtZeroDiversity
            0.1,
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            1.2, // happinessValueAtZeroDiversity
            0.1,
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at one is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            0.2, 
            -0.1, // happinessValueAtOneDiversity
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            0.2, 
            1.1, // happinessValueAtOneDiversity
            0.0
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if diverstiyWhereDropHappens is less than 0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            0.2, 
            0.1,
            -0.1 //diversityWhereDropHappens
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if diverstiyWhereDropHappens is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            0.2, 
            0.1,
            1.1 //diversityWhereDropHappens
        ), 
        Contains("must be between 0.0 and 1.0 inclusive.")
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if"
" happinessValueAtZeroDiversity is smaller than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            0.1, //happinessValueAtZeroDiversity
            0.2, //happinessValueAtOneDiversity
            0.0 
        ),
        Contains(
            "happinessAtZeroDiversity must be"
            " larger than happinessAtOneDiversity."
        )
    );
}

TEST_CASE("Resident_StepDown Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepDown(
            0, 
            2, 
            0.0, 
            0.0,
            0.2, //happinessValueAtZeroDiversity
            0.2, //happinessValueAtOneDiversity
            0.0 
        ),
        Contains(
            "happinessAtZeroDiversity must be"
            " larger than happinessAtOneDiversity."
        )
    );
}

TEST_CASE("getHappiness() returns lowered happinessValue at point where drop happens.")
{
    // Note @diversityWhereDropHappens is 0.25.
    Resident_StepDown greenResident{ 
        0, 
        2, 
        0.0,  
        0.0,
        0.2, // happinessValueAtZeroDiversity
        0.1, // happinessValueAtOneDiversity
        0.25  // diversityWhereDropHappens
    };

    // Diversity Ratio is 0.25. 
    std::set<Resident*> neighbors = { 
        &greenNeighbor1,
        &greenNeighbor2,
        &greenNeighbor3,
        &blueNeighbor1
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.1);
}

TEST_CASE("getHappiness() returns higher happinessValue before diversity drop.")
{
    // Note @diversityWhereDropHappens is 0.5.
    Resident_StepDown greenResident{ 
        0, 
        2, 
        0.0,  
        0.0, 
        0.2, // happinessValueAtZeroDiversity
        0.1, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };

    // Diversity Ratio is 0.25.
    std::set<Resident*> neighbors = { 
        &blueNeighbor1,
        &greenNeighbor1,
        &greenNeighbor2,
        &greenNeighbor3
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.2);
}

TEST_CASE("getHappines() returns lower happinessValue afterDiversity drop.")
{
    // Note @diversityWhereDropHappens is 0.25. 
    Resident_StepDown greenResident{ 
        0, 
        2, 
        0.0, 
        0.0,
        0.2,
        0.1,
        0.5
    };

    // Diversity Ratio is 0.25.
    std::set<Resident*> neighbors = { 
        &blueNeighbor1,
        &blueNeighbor2,
        &blueNeighbor3,
        &greenNeighbor1,
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.1);
}

TEST_CASE("Resident_StepDown toStrBasic()")
{
    Resident_StepDown greenResident{ 
        1, 
        2, 
        0.0,  // allowedMovementDistance
        0.25, // happinessGoal
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
        0.5   // diversityWhereDropHappens
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_StepDown(id, clr, mov, goal, hap0, hap1, drop):"
        " (1, green, 0.000000, 0.250000, 0.750000, 0.250000, 0.500000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

House hh0 = House{0};
House hh1 = House{1};
House hh2 = House{2};
House hh3 = House{3};
House hh4 = House{4};
House hh5 = House{5};
House hh6 = House{6};
House hh7 = House{7};
House hh8 = House{8};
House hh9 = House{9};
House hh10 = House{10};
House hh11 = House{11};
House hh12 = House{12};
House hh13 = House{13};
House hh14 = House{14};
House hh15 = House{15};
House hh16 = House{16};
House hh17 = House{17};
House hh18 = House{18};
House hh19 = House{19};
House hh20 = House{20};
House hh21 = House{21};
House hh22 = House{22};
House hh23 = House{23};
House hh24 = House{24};

TEST_CASE("Resident_StepDown findHome()"
    " green resident has choice of one green neigbor or one blue neigbor,"
    " chooses green neighbor")
{
    Resident_StepDown greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        0.5,  // happinessValueAtZeroDiversity
        0.1,  // happinessValueAtOneDiversity
        0.5   // stepDown Diversity x-value
    };

    House& oldHouse = hh0; // resident's current house
    House& grHouse8 = hh8;  // green resident lives in house 8
    House& blHouse16 = hh16; // blue resident lives in house 16
    House& house11 = hh11; // next to blue resident
    House& house13 = hh13; // next to green resident

    std::set<House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&hh7);
    housesAdjToHouse13.insert(&hh8);
    housesAdjToHouse13.insert(&hh9);
    housesAdjToHouse13.insert(&hh12);
    housesAdjToHouse13.insert(&hh14);
    housesAdjToHouse13.insert(&hh17);
    housesAdjToHouse13.insert(&hh18);
    housesAdjToHouse13.insert(&hh19);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hh5);
    housesAdjToHouse11.insert(&hh6);
    housesAdjToHouse11.insert(&hh7);
    housesAdjToHouse11.insert(&hh10);
    housesAdjToHouse11.insert(&hh12);
    housesAdjToHouse11.insert(&hh15);
    housesAdjToHouse11.insert(&hh16);
    housesAdjToHouse11.insert(&hh17);

    std::map<House*, std::set<House*>> openHousesAndTheirAdjHouses;
    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house13,
        housesAdjToHouse13
        )
    );
    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house11,
        housesAdjToHouse11)
    );

    std::map<House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor1));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor1));
        
    REQUIRE(
        greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        ) ==
        &house13
    );

}

TEST_CASE("Resident_StepDown findHome()"
    " green resident has choice of a) two green neigbors, b) two green + 1 blue neighbors,"
    " or c) one blue plus one green neigbor, chooses either a) or b).")
{ 
    Resident_StepDown greenResident{ 
        1, 
        2, 
        0.0, // allowed movement
        0.6, // happiness Goal
        1.0, // happinessValueAtZeroDiversity
        0.0, // happinessValueAtOneDiversity
        0.5  // drop location 
    };

    House& oldHouse  = hh0;  // resident's current house
    House& grHouse7  = hh7;  // green resident lives in house 7
    House& grHouse8  = hh8;  // green resident lives in house 8
    House& blHouse16 = hh16; // blue resident lives in house 16
    House& house2  = hh2;  // next to two green residents (happiness = 1.0)
    House& house11 = hh11; // next to one blue resident + one green resident (happiness = 0.0)
    House& house12 = hh12; // next to two green + one blue residents (happiness = 1.0)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&hh1);
    housesAdjToHouse2.insert(&hh3);
    housesAdjToHouse2.insert(&hh6);
    housesAdjToHouse2.insert(&hh7);
    housesAdjToHouse2.insert(&hh8);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hh5);
    housesAdjToHouse11.insert(&hh6);
    housesAdjToHouse11.insert(&hh7);
    housesAdjToHouse11.insert(&hh10);
    housesAdjToHouse11.insert(&hh12);
    housesAdjToHouse11.insert(&hh15);
    housesAdjToHouse11.insert(&hh16);
    housesAdjToHouse11.insert(&hh17);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&hh6);
    housesAdjToHouse12.insert(&hh7);
    housesAdjToHouse12.insert(&hh8);
    housesAdjToHouse12.insert(&hh11);
    housesAdjToHouse12.insert(&hh13);
    housesAdjToHouse12.insert(&hh16);
    housesAdjToHouse12.insert(&hh17);
    housesAdjToHouse12.insert(&hh18);

    std::map<House*, std::set<House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house11,
        housesAdjToHouse11)
    );

    std::map<House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7,&greenNeighbor1));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor2));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor1));
    
    House* answerHouse = greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE( (answerHouse == &house12 || answerHouse == &house2) );
}

TEST_CASE("Resident_StepDown findBestHome()"
    " green resident has choice of a) two green + 1 blue neighbors,"
    " or b) one blue plus one green neigbor, chooses either a) or b).")
{ 
    Resident_StepDown greenResident{ 
        1, 
        2, 
        0.0, // allowed movement
        0.6, // happiness Goal
        1.0, // happinessValueAtZeroDiversity
        0.0, // happinessValueAtOneDiversity
        0.5  // drop location 
    };

    House& oldHouse  = hh0;  // resident's current house
    House& grHouse7  = hh7;  // green resident lives in house 7
    House& grHouse8  = hh8;  // green resident lives in house 8
    House& blHouse16 = hh16; // blue resident lives in house 16
    House& house11 = hh11; // next to one blue resident + one green resident (happiness = 0.0)
    House& house12 = hh12; // next to two green + one blue residents (happiness = 1.0)

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hh5);
    housesAdjToHouse11.insert(&hh6);
    housesAdjToHouse11.insert(&hh7);
    housesAdjToHouse11.insert(&hh10);
    housesAdjToHouse11.insert(&hh12);
    housesAdjToHouse11.insert(&hh15);
    housesAdjToHouse11.insert(&hh16);
    housesAdjToHouse11.insert(&hh17);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&hh6);
    housesAdjToHouse12.insert(&hh7);
    housesAdjToHouse12.insert(&hh8);
    housesAdjToHouse12.insert(&hh11);
    housesAdjToHouse12.insert(&hh13);
    housesAdjToHouse12.insert(&hh16);
    housesAdjToHouse12.insert(&hh17);
    housesAdjToHouse12.insert(&hh18);

    std::map<House*, std::set<House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house11,
        housesAdjToHouse11)
    );

    std::map<House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7,&greenNeighbor1));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor2));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor1));
    
    House* answerHouse = greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE( answerHouse == &house12 );
}