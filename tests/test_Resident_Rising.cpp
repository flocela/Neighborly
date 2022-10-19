#include "catch.hpp"
#include "../src/Resident_Rising.h"
#include "../src/Resident_Flat.h"
#include <set>
using Catch::Matchers::Contains;

// Neighbors are used in getHappiness() method.
// Only arugment that matteres is Color argument.
Resident_Flat blueNeighbor0001{1, 1, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor0002{2, 1, 0.0, 0.0, 0.0 };

Resident_Flat blueNeighbor0003{3, 1, 0.0, 0.0, 0.0 };
    
Resident_Flat greenNeighbor0001{1, 2, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor0002{2, 2, 0.0, 0.0, 0.0 };

Resident_Flat greenNeighbor0003{3, 2, 0.0, 0.0, 0.0 };

TEST_CASE("Resident_Rising Ctor throws exception if happinessGoal is less than 0.0")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            -0.25, // happiness goal
            1.0,
            0.1,
            0.2
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );
} 

TEST_CASE("Resident_Rising Ctor throws exception if happinessGoal is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0, 
            1.2, // happiness goal
            1.0,
            0.1, 
            0.2 
        ), 
        Contains("must be between 0.0 and 1.0 inclusive") 
    );

}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at zero is less than 0.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            -0.3, // value at zero Diversity
            0.2
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at zero is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            1.2, // value at zero Diversity
            0.2
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at one is less than zero.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            0.1,
            -0.3 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if happinessValue at one is greater than 1.0.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            0.1,
            1.2 // value at one Diversity
        ), 
        Contains("must be between 0.0 and 1.0 inclusive")
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if"
" happinessValueAtZeroDiversity is larger than happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            .2, // value at zero Diversity
            .1  // value at one Diversity
        ), 
        Contains("hapinessAtOneDiversity must be larger than at"
            " happinessAtZeroDiversity."
        )
    );
}

TEST_CASE("Resident_Rising Ctor throws exception if"
" happinessValueAtZeroDiversity is the same as happinessValueAtOneDiversity.")
{   
    REQUIRE_THROWS_WITH(
        Resident_Rising(
            0, 
            2, 
            0.0,
            0.0,
            1.0,
            .75,
            .75
        ), 
        Contains("hapinessAtOneDiversity must be larger than at"
            " happinessAtZeroDiversity.")
    );
}

TEST_CASE("Residnt_Rising getHappiness()")
{
    Resident_Rising greenResident{ 
        0, 
        2, 
        0.0,  
        0.0,
        1.0,
        0.2, // happinessValueAtZeroDiversity
        0.8, // happinessValueAtOneDiversity
    };

    std::set<Resident*> neighbors = { 
        &greenNeighbor0001,
        &greenNeighbor0002,
        &greenNeighbor0003,
        &blueNeighbor0001
    };

    REQUIRE(( greenResident.calculateHappiness(neighbors, 4) - 0.35) > -0.001);
    REQUIRE(( greenResident.calculateHappiness(neighbors, 4) - 0.35) < 0.001);
}

TEST_CASE("Resident_Rising toStrBasic()")
{
    Resident_Rising greenResident{ 
        1, 
        2, 
        0.0,  
        0.25,
        1.0,
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_Rising(id, clr, mov, goal, hap0, hap1):"
        " (1, green_neutral, 0.000000, 0.250000, 0.250000, 0.750000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

const House h000 = House{0};
const House h001 = House{1};
const House h002 = House{2};
const House h003 = House{3};
const House h004 = House{4};
const House h005 = House{5};
const House h006 = House{6};
const House h007 = House{7};
const House h008 = House{8};
const House h009 = House{9};
const House h010 = House{10};
const House h011 = House{11};
const House h012 = House{12};
const House h013 = House{13};
const House h014 = House{14};
const House h015 = House{15};
const House h016 = House{16};
const House h017 = House{17};
const House h018 = House{18};
const House h019 = House{19};
const House h020 = House{20};
const House h021 = House{21};
const House h022 = House{22};
const House h023 = House{23};
const House h024 = House{24};

TEST_CASE("Resident_Rising findHome()"
    " green_neutral resident has choice of one green_neutral neigbor or one blue_neutral neigbor,"
    " chooses blue_neutral neighbor")
{
    Resident_Rising greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        1.0,
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
    };

    const House& oldHouse = h000;  // resident's current house
    const House& grHouse8 = h008;  // green_neutral resident lives in house 8
    const House& blHouse16 = h016; // blue_neutral resident lives in house 16
    const House& house11 = h011;   // next to blue_neutral resident
    const House& house13 = h013;   // next to green_neutral resident

    std::set<const House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&h007);
    housesAdjToHouse13.insert(&h008);
    housesAdjToHouse13.insert(&h009);
    housesAdjToHouse13.insert(&h012);
    housesAdjToHouse13.insert(&h014);
    housesAdjToHouse13.insert(&h017);
    housesAdjToHouse13.insert(&h018);
    housesAdjToHouse13.insert(&h019);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h005);
    housesAdjToHouse11.insert(&h006);
    housesAdjToHouse11.insert(&h007);
    housesAdjToHouse11.insert(&h010);
    housesAdjToHouse11.insert(&h012);
    housesAdjToHouse11.insert(&h015);
    housesAdjToHouse11.insert(&h016);
    housesAdjToHouse11.insert(&h017);

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
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&greenNeighbor0001));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blueNeighbor0001));
        
    REQUIRE(
        greenResident.findHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        ) ==
        &house11
    );

}

TEST_CASE("Resident_Falling findHome()"
    " blue_neutral resident has choice of a) two green_neutral neigbors, b) one green_neutral plus"
    " one blue_neutral residents, c) two green_neutral and one blue_neutral residents"
    " chooses either a) or c).")
{   
    Resident_Rising blueResident{ 
        1, 
        1, 
        0.0,  // allowed movement
        0.6, // happiness Goal
        1.0,
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
    };

    const House& oldHouse = h000;  // resident's current house
    const House& grHouse7 = h007;   // green_neutral resident lives in house 7
    const House& grHouse8 = h008;   // green_neutral resident lives in house 8
    const House& blHouse16 = h016;  // blue_neutral resident lives in house 16
    const House& house2  = h002; // next to two green_neutral residents (happiness = 1.0)
    const House& house11 = h011; // next to one green_neutral + one blue_neutral residents (happiness = 0.5)
    const House& house12 = h012; // next to two green_neutral + one blue_neutral residents (happiness = 0.66)

    std::set<const House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h001);
    housesAdjToHouse2.insert(&h003);
    housesAdjToHouse2.insert(&h006);
    housesAdjToHouse2.insert(&h007);
    housesAdjToHouse2.insert(&h008);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h005);
    housesAdjToHouse11.insert(&h006);
    housesAdjToHouse11.insert(&h007);
    housesAdjToHouse11.insert(&h010);
    housesAdjToHouse11.insert(&h012);
    housesAdjToHouse11.insert(&h015);
    housesAdjToHouse11.insert(&h016);
    housesAdjToHouse11.insert(&h017);

    std::set<const House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h006);
    housesAdjToHouse12.insert(&h007);
    housesAdjToHouse12.insert(&h008);
    housesAdjToHouse12.insert(&h011);
    housesAdjToHouse12.insert(&h013);
    housesAdjToHouse12.insert(&h016);
    housesAdjToHouse12.insert(&h017);
    housesAdjToHouse12.insert(&h018);

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
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse7,&greenNeighbor0001));
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&greenNeighbor0002));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blueNeighbor0001));
    
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

TEST_CASE("Resident_Falling findBestHome()"
    " blue_neutral resident has choice of a) two green_neutral neigbors, b) one green_neutral plus"
    " one blue_neutral residents, c) two green_neutral and one blue_neutral residents"
    " chooses either a).")
{   std::cout << "testResident rising findHouse() "<< std::endl;
    Resident_Rising blueResident{ 
        1, 
        1, 
        0.0,  // allowed movement
        0.6, // happiness Goal
        1.0,
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
    };

    const House& oldHouse = h000;  // resident's current house
    const House& grHouse7 = h007;   // green_neutral resident lives in house 7
    const House& grHouse8 = h008;   // green_neutral resident lives in house 8
    const House& blHouse16 = h016;  // blue_neutral resident lives in house 16
    const House& house2  = h002; // next to two green_neutral residents (happiness = 1.0)
    const House& house11 = h011; // next to one green_neutral + one blue_neutral residents (happiness = 0.5)
    const House& house12 = h012; // next to two green_neutral + one blue_neutral residents (happiness = 0.66)

    std::set<const House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h001);
    housesAdjToHouse2.insert(&h003);
    housesAdjToHouse2.insert(&h006);
    housesAdjToHouse2.insert(&h007);
    housesAdjToHouse2.insert(&h008);

    std::set<const House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h005);
    housesAdjToHouse11.insert(&h006);
    housesAdjToHouse11.insert(&h007);
    housesAdjToHouse11.insert(&h010);
    housesAdjToHouse11.insert(&h012);
    housesAdjToHouse11.insert(&h015);
    housesAdjToHouse11.insert(&h016);
    housesAdjToHouse11.insert(&h017);

    std::set<const House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h006);
    housesAdjToHouse12.insert(&h007);
    housesAdjToHouse12.insert(&h008);
    housesAdjToHouse12.insert(&h011);
    housesAdjToHouse12.insert(&h013);
    housesAdjToHouse12.insert(&h016);
    housesAdjToHouse12.insert(&h017);
    housesAdjToHouse12.insert(&h018);

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
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse7,&greenNeighbor0001));
    houseToResMap.insert(std::pair<const House*, Resident*>(&grHouse8,&greenNeighbor0002));
    houseToResMap.insert(std::pair<const House*, Resident*>(&blHouse16, &blueNeighbor0001));
    
    const House* answerHouse = blueResident.findBestHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE((
        answerHouse == &house2
    ));

}