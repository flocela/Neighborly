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
        0.75, // happinessValueAtZeroDiversity
        0.25, // happinessValueAtOneDiversity
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_Falling(id, clr, mov, goal, hap0, hap1):"
        " (1, green, 0.000000, 0.250000, 0.750000, 0.250000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

House h0 = House{0};
House h1 = House{1};
House h2 = House{2};
House h3 = House{3};
House h4 = House{4};
House h5 = House{5};
House h6 = House{6};
House h7 = House{7};
House h8 = House{8};
House h9 = House{9};
House h10 = House{10};
House h11 = House{11};
House h12 = House{12};
House h13 = House{13};
House h14 = House{14};
House h15 = House{15};
House h16 = House{16};
House h17 = House{17};
House h18 = House{18};
House h19 = House{19};
House h20 = House{20};
House h21 = House{21};
House h22 = House{22};
House h23 = House{23};
House h24 = House{24};

TEST_CASE("Resident_Falling findHome()"
    " green resident has choice of one green neigbor or one blue neigbor,"
    " chooses green neighbor")
{
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        0.5,  // happinessValueAtZeroDiversity
        0.1,  // happinessValueAtOneDiversity
    };

    House& oldHouse = h0; // resident's current house
    House& grHouse8 = h8;  // green resident lives in house 8
    House& blHouse16 = h16; // blue resident lives in house 16
    House& house11  = h11; // next to blue resident
    House& house13  = h13; // next to green resident

    std::set<House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&h7);
    housesAdjToHouse13.insert(&h8);
    housesAdjToHouse13.insert(&h9);
    housesAdjToHouse13.insert(&h12);
    housesAdjToHouse13.insert(&h14);
    housesAdjToHouse13.insert(&h17);
    housesAdjToHouse13.insert(&h18);
    housesAdjToHouse13.insert(&h19);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h5);
    housesAdjToHouse11.insert(&h6);
    housesAdjToHouse11.insert(&h7);
    housesAdjToHouse11.insert(&h10);
    housesAdjToHouse11.insert(&h12);
    housesAdjToHouse11.insert(&h15);
    housesAdjToHouse11.insert(&h16);
    housesAdjToHouse11.insert(&h17);

    std::map<House*, std::set<House*>> openHousesAndTheirAdjHouses;
    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &h13,
        housesAdjToHouse13
        )
    );
    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &h11,
        housesAdjToHouse11)
    );

    std::map<House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor001));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor001));
        
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
    " green resident has choice of a) two green neigbors, b) two green + 1 blue neighbors,"
    " or c) one blue plus one green neigbor, chooses either a) or b).")
{ 
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.6,  // happiness Goal
        1.0,  // happinessValueAtZeroDiversity
        0.0,  // happinessValueAtOneDiversity
    };

    House& oldHouse  = h0;  // resident's current house
    House& grHouse7  = h7;  // green resident lives in house 7
    House& grHouse8  = h8;  // green resident lives in house 8
    House& blHouse16 = h16; // blue resident lives in house 16
    House& house2  = h2;  // next to two green residents (happiness = 1.0)
    House& house11 = h11; // next to one blue resident + one green resident (happiness = 0.5)
    House& house12 = h12; // next to two green + one blue residents (happiness = 0.66)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h1);
    housesAdjToHouse2.insert(&h3);
    housesAdjToHouse2.insert(&h6);
    housesAdjToHouse2.insert(&h7);
    housesAdjToHouse2.insert(&h8);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h5);
    housesAdjToHouse11.insert(&h6);
    housesAdjToHouse11.insert(&h7);
    housesAdjToHouse11.insert(&h10);
    housesAdjToHouse11.insert(&h12);
    housesAdjToHouse11.insert(&h15);
    housesAdjToHouse11.insert(&h16);
    housesAdjToHouse11.insert(&h17);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h6);
    housesAdjToHouse12.insert(&h7);
    housesAdjToHouse12.insert(&h8);
    housesAdjToHouse12.insert(&h11);
    housesAdjToHouse12.insert(&h13);
    housesAdjToHouse12.insert(&h16);
    housesAdjToHouse12.insert(&h17);
    housesAdjToHouse12.insert(&h18);

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
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7,&greenNeighbor001));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor002));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor001));
    
    House* answerHouse = greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE( (answerHouse == &house12 || answerHouse == &house2) );

}

TEST_CASE("Resident_Falling findBestHome()"
    " green resident has choice of a) two green neigbors, b) two green + 1 blue neighbors,"
    " or c) one blue plus one green neigbor, chooses a).")
{  
    Resident_Falling greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.6,  // happiness Goal
        1.0,  // happinessValueAtZeroDiversity
        0.0,  // happinessValueAtOneDiversity
    };

    House& oldHouse = h0;  // resident's current house
    House& grHouse7 = h7;  // green resident lives in house 7
    House& grHouse8 = h8;  // green resident lives in house 8
    House& blHouse16 = h16; // blue resident lives in house 16
    House& house2    = h2;  // next to two green residents (happiness = 1.0)
    House& house11   = h11; // next to one blue resident + one green resident (happiness = 0.5)
    House& house12   = h12; // next to two green + one blue residents (happiness = 0.66)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h1);
    housesAdjToHouse2.insert(&h3);
    housesAdjToHouse2.insert(&h6);
    housesAdjToHouse2.insert(&h7);
    housesAdjToHouse2.insert(&h8);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h5);
    housesAdjToHouse11.insert(&h6);
    housesAdjToHouse11.insert(&h7);
    housesAdjToHouse11.insert(&h10);
    housesAdjToHouse11.insert(&h12);
    housesAdjToHouse11.insert(&h15);
    housesAdjToHouse11.insert(&h16);
    housesAdjToHouse11.insert(&h17);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h6);
    housesAdjToHouse12.insert(&h7);
    housesAdjToHouse12.insert(&h8);
    housesAdjToHouse12.insert(&h11);
    housesAdjToHouse12.insert(&h13);
    housesAdjToHouse12.insert(&h16);
    housesAdjToHouse12.insert(&h17);
    housesAdjToHouse12.insert(&h18);

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
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7,&greenNeighbor001));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor002));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor001));
    
    House* answerHouse = greenResident.findBestHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE( answerHouse == &house2 );

}