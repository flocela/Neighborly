#include "catch.hpp"
#include "../src/Resident_StepUp.h"
#include "../src/Resident_Flat.h"
using Catch::Matchers::Contains;


// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blNeighbor01{1, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blNeighbor02{2, Color::blue, 0.0, 0.0, 0.0 };

Resident_Flat blNeighbor03{3, Color::blue, 0.0, 0.0, 0.0 };
    
Resident_Flat grNeighbor01{1, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat grNeighbor02{2, Color::green, 0.0, 0.0, 0.0 };

Resident_Flat grNeighbor03{3, Color::green, 0.0, 0.0, 0.0 };
    

TEST_CASE("Resident_StepUp Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_StepUp(
            0, 
            Color::green, 
            0,
            1.2, // happinessGoal
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
            Color::green, 
            0,
            -.1, // happinessGoal
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
            Color::green, 
            0,
            0,
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
        Color::green, 
        0.0,  
        0.25,
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
        Color::blue, 
        0.0,  
        0.0, 
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
        Color::blue, 
        0.0, 
        0.0,
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
        Color::green, 
        0.0,  // allowedMovementDistance 
        0.25, // happinessGoal
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
        0.5   // diversityWhereRiseHappens
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_StepUp(id, clr, mov, goal, hap0, hap1, rise):"
        " (1, green, 0.000000, 0.250000, 0.250000, 0.750000, 0.500000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

House hs000 = House{0};
House hs001 = House{1};
House hs002 = House{2};
House hs003 = House{3};
House hs004 = House{4};
House hs005 = House{5};
House hs006 = House{6};
House hs007 = House{7};
House hs008 = House{8};
House hs009 = House{9};
House hs010 = House{10};
House hs011 = House{11};
House hs012 = House{12};
House hs013 = House{13};
House hs014 = House{14};
House hs015 = House{15};
House hs016 = House{16};
House hs017 = House{17};
House hs018 = House{18};
House hs019 = House{19};
House hs020 = House{20};
House hs021 = House{21};
House hs022 = House{22};
House hs023 = House{23};
House hs024 = House{24};

TEST_CASE("Resident_StepUp findHome()"
    " green resident has choice of one green neigbor or one blue neighbor,"
    " chooses blue neighbor")
{
    Resident_StepUp greenResident{ 
        1, 
        Color::green, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
        0.5   // location of rise
    };

    House& oldHouse = hs000;  // resident's current house
    House& grHouse8 = hs008;  // green resident lives in house 8
    House& blHouse16 = hs016; // blue resident lives in house 16
    House& house11 = hs011;   // next to blue resident
    House& house13 = hs013;   // next to green resident

    std::set<House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&hs007);
    housesAdjToHouse13.insert(&hs008);
    housesAdjToHouse13.insert(&hs009);
    housesAdjToHouse13.insert(&hs012);
    housesAdjToHouse13.insert(&hs014);
    housesAdjToHouse13.insert(&hs017);
    housesAdjToHouse13.insert(&hs018);
    housesAdjToHouse13.insert(&hs019);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hs005);
    housesAdjToHouse11.insert(&hs006);
    housesAdjToHouse11.insert(&hs007);
    housesAdjToHouse11.insert(&hs010);
    housesAdjToHouse11.insert(&hs012);
    housesAdjToHouse11.insert(&hs015);
    housesAdjToHouse11.insert(&hs016);
    housesAdjToHouse11.insert(&hs017);

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
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&grNeighbor01));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blNeighbor01));
        
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
    " blue resident has choice of a) two green neigbors, b) one green plus"
    " one blue residents, c) two green and one blue residents"
    " chooses either a) or c).")
{   
    Resident_StepUp blueResident{ 
        1, 
        Color::blue, 
        0.0, // allowed movement
        0.6, // happiness Goal
        0.0, // happinessValueAtZeroDiversity
        1.0, // happinessValueAtOneDiversity
        0.65  // location of rise
    };

    House& oldHouse = hs000;  // resident's current house
    House& grHouse7 = hs007;   // green resident lives in house 7
    House& grHouse8 = hs008;   // green resident lives in house 8
    House& blHouse16 = hs016;  // blue resident lives in house 16
    House& house2  = hs002; // next to two green residents (happiness = 1.0)
    House& house11 = hs011; // next to one green + one blue residents (happiness = 0.0)
    House& house12 = hs012; // next to two green + one blue residents (happiness = 1.0)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&hs001);
    housesAdjToHouse2.insert(&hs003);
    housesAdjToHouse2.insert(&hs006);
    housesAdjToHouse2.insert(&hs007);
    housesAdjToHouse2.insert(&hs008);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hs005);
    housesAdjToHouse11.insert(&hs006);
    housesAdjToHouse11.insert(&hs007);
    housesAdjToHouse11.insert(&hs010);
    housesAdjToHouse11.insert(&hs012);
    housesAdjToHouse11.insert(&hs015);
    housesAdjToHouse11.insert(&hs016);
    housesAdjToHouse11.insert(&hs017);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&hs006);
    housesAdjToHouse12.insert(&hs007);
    housesAdjToHouse12.insert(&hs008);
    housesAdjToHouse12.insert(&hs011);
    housesAdjToHouse12.insert(&hs013);
    housesAdjToHouse12.insert(&hs016);
    housesAdjToHouse12.insert(&hs017);
    housesAdjToHouse12.insert(&hs018);

    std::map<House*, std::set<House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house11,
        housesAdjToHouse11)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    std::map<House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7, &grNeighbor01));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8, &grNeighbor02));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blNeighbor01));
    
    House* answerHouse = blueResident.findHome(
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
    " blue resident has choice of a) two green neigbors, b) one green plus"
    " one blue residents, c) two green and one blue residents"
    " chooses either a) or c).")
{   
    Resident_StepUp blueResident{ 
        1, 
        Color::blue, 
        0.0, // allowed movement
        0.6, // happiness Goal
        0.0, // happinessValueAtZeroDiversity
        1.0, // happinessValueAtOneDiversity
        0.65  // location of rise
    };

    House& oldHouse = hs000;  // resident's current house
    House& grHouse7 = hs007;   // green resident lives in house 7
    House& grHouse8 = hs008;   // green resident lives in house 8
    House& blHouse16 = hs016;  // blue resident lives in house 16
    House& house2  = hs002; // next to two green residents (happiness = 1.0)
    House& house11 = hs011; // next to one green + one blue residents (happiness = 0.0)
    House& house12 = hs012; // next to two green + one blue residents (happiness = 1.0)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&hs001);
    housesAdjToHouse2.insert(&hs003);
    housesAdjToHouse2.insert(&hs006);
    housesAdjToHouse2.insert(&hs007);
    housesAdjToHouse2.insert(&hs008);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&hs005);
    housesAdjToHouse11.insert(&hs006);
    housesAdjToHouse11.insert(&hs007);
    housesAdjToHouse11.insert(&hs010);
    housesAdjToHouse11.insert(&hs012);
    housesAdjToHouse11.insert(&hs015);
    housesAdjToHouse11.insert(&hs016);
    housesAdjToHouse11.insert(&hs017);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&hs006);
    housesAdjToHouse12.insert(&hs007);
    housesAdjToHouse12.insert(&hs008);
    housesAdjToHouse12.insert(&hs011);
    housesAdjToHouse12.insert(&hs013);
    housesAdjToHouse12.insert(&hs016);
    housesAdjToHouse12.insert(&hs017);
    housesAdjToHouse12.insert(&hs018);

    std::map<House*, std::set<House*>> openHousesAndTheirAdjHouses;

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house2,
        housesAdjToHouse2)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house11,
        housesAdjToHouse11)
    );

    openHousesAndTheirAdjHouses.insert(std::pair<House*, std::set<House*>>(
        &house12,
        housesAdjToHouse12
        )
    );

    std::map<House*, Resident*> houseToResMap;
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7, &grNeighbor01));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8, &grNeighbor02));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blNeighbor01));
    
    House* answerHouse = blueResident.findBestHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
        
    REQUIRE((
        
        answerHouse == &house2 ||
        answerHouse == &house12
    ));

}
