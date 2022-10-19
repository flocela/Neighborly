#include "catch.hpp"
#include "../src/Resident_StepUp.h"
#include "../src/Resident_Flat.h"
using Catch::Matchers::Contains;


// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blNeighbor01{1, 1, 0.0, 0.0, 0.0 };

Resident_Flat blNeighbor02{2, 1, 0.0, 0.0, 0.0 };

Resident_Flat blNeighbor03{3, 1, 0.0, 0.0, 0.0 };
    
Resident_Flat grNeighbor01{1, 2, 0.0, 0.0, 0.0 };

Resident_Flat grNeighbor02{2, 2, 0.0, 0.0, 0.0 };

Resident_Flat grNeighbor03{3, 2, 0.0, 0.0, 0.0 };
    

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            1.2, // happinessGoal
            1.0,
            0.0,
            .1,
            0.2
        ),
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            -.1, // happinessGoal
            1.0,
            0.1,
            0.2,
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            -.1, // happinessValueAtZeroDiversity 
            .1,
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            1.2, // happinessValueAtZeroDiversity 
            .1,
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at one is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            0.2,  
            -.1, // happinessValueAtOneDiversity
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            0.2,  
            1.1, // happinessValueAtOneDiversity
            0
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if diversityWhereRiseHappens is less than 0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            0.1,  
            0.2,
            -.1 // diversityWhereRiseHappens
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if diverstiyWhereRiseHappens is greater than 1.0.")
{   
   REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            0.1,  
            0.2,
            1.1 // diversityWhereRiseHappens
        ),
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if"
" happinessValueAtZeroDiversity is larger than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            .75, //happinessValueAtZeroDiversity
            .25, //happinessValueAtOneDiversity
            0), 
        Contains("happinessAtZeroDiversity must be smaller than"
            " happinessAtOneDiversity.")
    );
}

TEST_CASE("Resident_StepUp Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            2, 
            0,
            0,
            1.0,
            .75, // happinessValueAtZeroDiversity
            .75, // happinessValueAtOneDiversity
            0), 
        Contains("happinessAtZeroDiversity must be smaller than"
            " happinessAtOneDiversity.")
    );
}

TEST_CASE("getHappines() returns higher happinessValue at point where rise happens.")
{   
    // Note @diverstiyWhereRiseHappens is 0.50.
    Resident_StepUp greenResident{ 
        0, 
        2, 
        0.0,  
        0.25,
        1.0,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.50  // diversityWhereRiseHappens
    };

    // diversity Ratio is 0.5.
    std::set<Resident*> neighbors = { 
        &grNeighbor01,
        &grNeighbor02,
        &blNeighbor01,
        &blNeighbor02
    };

    REQUIRE(greenResident.calculateHappiness(neighbors, 4) == 0.75);
}

TEST_CASE("getHappines() returns lower happinessValue before diversity rise.")
{
    // Note @diverstiyWhereRiseHappens is 0.5.
    Resident_StepUp blueResident{ 
        0, 
        1, 
        0.0,  
        0.0,
        1.0,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };

    // Diversity Ratio is 0.25. 
    std::set<Resident*> neighbors = { 
        &blNeighbor01,
        &blNeighbor02,
        &blNeighbor03,
        &grNeighbor01
    };

    REQUIRE(blueResident.calculateHappiness(neighbors, 4) == 0.25);
}

TEST_CASE("getHappiness() returns higher happinessValue afterDiversity rise.")
{
    // Note @diverstiyWhereDropHappens is 0.5.
    Resident_StepUp blueResident{ 
        0, 
        1, 
        0.0, 
        0.0,
        1.0,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };

    // Diversity Ratio is 0.75.
    std::set<Resident*> neighbors = { 
        &blNeighbor01,
        &grNeighbor01,
        &grNeighbor02,
        &grNeighbor03,
    };

    REQUIRE(blueResident.calculateHappiness(neighbors, 4) == 0.75);
}

TEST_CASE("Resident_StepUp toStrBasic()")
{
    Resident_StepUp greenResident{ 
        1, 
        2, 
        0.0,  // allowedMovementDistance 
        0.25, // happinessGoal
        1.0,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_StepUp(id, clr, mov, goal, hap0, hap1, rise):"
        " (1, green_neutral, 0.000000, 0.250000, 0.250000, 0.750000, 0.500000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

const House hs000 = House{0};
const House hs001 = House{1};
const House hs002 = House{2};
const House hs003 = House{3};
const House hs004 = House{4};
const House hs005 = House{5};
const House hs006 = House{6};
const House hs007 = House{7};
const House hs008 = House{8};
const House hs009 = House{9};
const House hs010 = House{10};
const House hs011 = House{11};
const House hs012 = House{12};
const House hs013 = House{13};
const House hs014 = House{14};
const House hs015 = House{15};
const House hs016 = House{16};
const House hs017 = House{17};
const House hs018 = House{18};
const House hs019 = House{19};
const House hs020 = House{20};
const House hs021 = House{21};
const House hs022 = House{22};
const House hs023 = House{23};
const House hs024 = House{24};

TEST_CASE("Resident_StepUp findHome()"
    " green_neutral resident has choice of one green_neutral neigbor or one blue_neutral neighbor,"
    " chooses blue_neutral neighbor")
{
    Resident_StepUp greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        1.0,
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
        0.5   // location of rise
    };

    const House& oldHouse = hs000;  // resident's current house
    const House& grHouse8 = hs008;  // green_neutral resident lives in house 8
    const House& blHouse16 = hs016; // blue_neutral resident lives in house 16
    const House& house11 = hs011;   // next to blue_neutral resident
    const House& house13 = hs013;   // next to green_neutral resident

    std::set<const House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&hs007);
    housesAdjToHouse13.insert(&hs008);
    housesAdjToHouse13.insert(&hs009);
    housesAdjToHouse13.insert(&hs012);
    housesAdjToHouse13.insert(&hs014);
    housesAdjToHouse13.insert(&hs017);
    housesAdjToHouse13.insert(&hs018);
    housesAdjToHouse13.insert(&hs019);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hs005);
    housesAdjToHouse11.insert(&hs006);
    housesAdjToHouse11.insert(&hs007);
    housesAdjToHouse11.insert(&hs010);
    housesAdjToHouse11.insert(&hs012);
    housesAdjToHouse11.insert(&hs015);
    housesAdjToHouse11.insert(&hs016);
    housesAdjToHouse11.insert(&hs017);

    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjHouses;
    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house13,
        housesAdjToHouse13
        )
    );
    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house11,
        housesAdjToHouse11)
    );

    std::unordered_map<const House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&grNeighbor01));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blNeighbor01));
        
    REQUIRE(
        greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        ) ==
        &house11
    );
}

TEST_CASE("Resident_StepUp findHome()"
    " blue_neutral resident has choice of a) two green_neutral neigbors, b) one green_neutral plus"
    " one blue_neutral residents, c) two green_neutral and one blue_neutral residents"
    " chooses either a) or c).")
{   
    Resident_StepUp blueResident{ 
        1, 
        1, 
        0.0, // allowed movement
        0.6, // happiness Goal
        1.0,
        0.0, // happinessValueAtZeroDiversity
        1.0, // happinessValueAtOneDiversity
        0.65  // location of rise
    };

    const House& oldHouse = hs000;  // resident's current house
    const House& grHouse7 = hs007;   // green_neutral resident lives in house 7
    const House& grHouse8 = hs008;   // green_neutral resident lives in house 8
    const House& blHouse16 = hs016;  // blue_neutral resident lives in house 16
    const House& house2  = hs002; // next to two green_neutral residents (happiness = 1.0)
    const House& house11 = hs011; // next to one green_neutral + one blue_neutral residents (happiness = 0.0)
    const House& house12 = hs012; // next to two green_neutral + one blue_neutral residents (happiness = 1.0)

    std::set<const House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&hs001);
    housesAdjToHouse2.insert(&hs003);
    housesAdjToHouse2.insert(&hs006);
    housesAdjToHouse2.insert(&hs007);
    housesAdjToHouse2.insert(&hs008);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hs005);
    housesAdjToHouse11.insert(&hs006);
    housesAdjToHouse11.insert(&hs007);
    housesAdjToHouse11.insert(&hs010);
    housesAdjToHouse11.insert(&hs012);
    housesAdjToHouse11.insert(&hs015);
    housesAdjToHouse11.insert(&hs016);
    housesAdjToHouse11.insert(&hs017);

    std::set<const House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&hs006);
    housesAdjToHouse12.insert(&hs007);
    housesAdjToHouse12.insert(&hs008);
    housesAdjToHouse12.insert(&hs011);
    housesAdjToHouse12.insert(&hs013);
    housesAdjToHouse12.insert(&hs016);
    housesAdjToHouse12.insert(&hs017);
    housesAdjToHouse12.insert(&hs018);

    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house11,
        housesAdjToHouse11)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    std::unordered_map<const House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse7, &grNeighbor01));
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8, &grNeighbor02));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blNeighbor01));
    
    const House* answerHouse = blueResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );

    REQUIRE((
        
        answerHouse == &house2 ||
        answerHouse == &house12
    ));

}

TEST_CASE("Resident_StepUp findBestHome()"
    " blue_neutral resident has choice of a) two green_neutral neigbors, b) one green_neutral plus"
    " one blue_neutral residents, c) two green_neutral and one blue_neutral residents"
    " chooses either a) or c).")
{   
    Resident_StepUp blueResident{ 
        1, 
        1, 
        0.0, // allowed movement
        0.6, // happiness Goal
        1.0,
        0.0, // happinessValueAtZeroDiversity
        1.0, // happinessValueAtOneDiversity
        0.65  // location of rise
    };

    const House& oldHouse = hs000;  // resident's current house
    const House& grHouse7 = hs007;   // green_neutral resident lives in house 7
    const House& grHouse8 = hs008;   // green_neutral resident lives in house 8
    const House& blHouse16 = hs016;  // blue_neutral resident lives in house 16
    const House& house2  = hs002; // next to two green_neutral residents (happiness = 1.0)
    const House& house11 = hs011; // next to one green_neutral + one blue_neutral residents (happiness = 0.0)
    const House& house12 = hs012; // next to two green_neutral + one blue_neutral residents (happiness = 1.0)

    std::set<const House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&hs001);
    housesAdjToHouse2.insert(&hs003);
    housesAdjToHouse2.insert(&hs006);
    housesAdjToHouse2.insert(&hs007);
    housesAdjToHouse2.insert(&hs008);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hs005);
    housesAdjToHouse11.insert(&hs006);
    housesAdjToHouse11.insert(&hs007);
    housesAdjToHouse11.insert(&hs010);
    housesAdjToHouse11.insert(&hs012);
    housesAdjToHouse11.insert(&hs015);
    housesAdjToHouse11.insert(&hs016);
    housesAdjToHouse11.insert(&hs017);

    std::set<const House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&hs006);
    housesAdjToHouse12.insert(&hs007);
    housesAdjToHouse12.insert(&hs008);
    housesAdjToHouse12.insert(&hs011);
    housesAdjToHouse12.insert(&hs013);
    housesAdjToHouse12.insert(&hs016);
    housesAdjToHouse12.insert(&hs017);
    housesAdjToHouse12.insert(&hs018);

    std::map<const House*, std::set<const House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house11,
        housesAdjToHouse11)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<const House*, std::set<const House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    std::unordered_map<const House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse7, &grNeighbor01));
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8, &grNeighbor02));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blNeighbor01));
    
    const House* answerHouse = blueResident.findBestHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
        
    REQUIRE((
        
        answerHouse == &house2 ||
        answerHouse == &house12
    ));

}
