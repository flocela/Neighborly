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
        0.25, // happinessValueAtZeroDiversity
        0.75, // happinessValueAtOneDiversity
    };
    REQUIRE(greenResident.toStrBasic() == 
        "Res_Rising(id, clr, mov, goal, hap0, hap1):"
        " (1, green, 0.000000, 0.250000, 0.250000, 0.750000)");
}

// findingHome() and findingBesHome() methods use this map
//    0   5   10   15   20
//    1   6   11   16   21
//    2   7   12   17   22
//    3   8   13   18   23
//    4   9   14   19   24

House h000 = House{0};
House h001 = House{1};
House h002 = House{2};
House h003 = House{3};
House h004 = House{4};
House h005 = House{5};
House h006 = House{6};
House h007 = House{7};
House h008 = House{8};
House h009 = House{9};
House h010 = House{10};
House h011 = House{11};
House h012 = House{12};
House h013 = House{13};
House h014 = House{14};
House h015 = House{15};
House h016 = House{16};
House h017 = House{17};
House h018 = House{18};
House h019 = House{19};
House h020 = House{20};
House h021 = House{21};
House h022 = House{22};
House h023 = House{23};
House h024 = House{24};

TEST_CASE("Resident_Rising findHome()"
    " green resident has choice of one green neigbor or one blue neigbor,"
    " chooses blue neighbor")
{
    Resident_Rising greenResident{ 
        1, 
        2, 
        0.0,  // allowed movement
        0.25, // happiness Goal
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
    };

    House& oldHouse = h000;  // resident's current house
    House& grHouse8 = h008;  // green resident lives in house 8
    House& blHouse16 = h016; // blue resident lives in house 16
    House& house11 = h011;   // next to blue resident
    House& house13 = h013;   // next to green resident

    std::set<House*> housesAdjToHouse13;
    housesAdjToHouse13.insert(&h007);
    housesAdjToHouse13.insert(&h008);
    housesAdjToHouse13.insert(&h009);
    housesAdjToHouse13.insert(&h012);
    housesAdjToHouse13.insert(&h014);
    housesAdjToHouse13.insert(&h017);
    housesAdjToHouse13.insert(&h018);
    housesAdjToHouse13.insert(&h019);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h005);
    housesAdjToHouse11.insert(&h006);
    housesAdjToHouse11.insert(&h007);
    housesAdjToHouse11.insert(&h010);
    housesAdjToHouse11.insert(&h012);
    housesAdjToHouse11.insert(&h015);
    housesAdjToHouse11.insert(&h016);
    housesAdjToHouse11.insert(&h017);

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
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor0001));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor0001));
        
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
    " blue resident has choice of a) two green neigbors, b) one green plus"
    " one blue residents, c) two green and one blue residents"
    " chooses either a) or c).")
{   
    Resident_Rising blueResident{ 
        1, 
        1, 
        0.0,  // allowed movement
        0.6, // happiness Goal
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
    };

    House& oldHouse = h000;  // resident's current house
    House& grHouse7 = h007;   // green resident lives in house 7
    House& grHouse8 = h008;   // green resident lives in house 8
    House& blHouse16 = h016;  // blue resident lives in house 16
    House& house2  = h002; // next to two green residents (happiness = 1.0)
    House& house11 = h011; // next to one green + one blue residents (happiness = 0.5)
    House& house12 = h012; // next to two green + one blue residents (happiness = 0.66)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h001);
    housesAdjToHouse2.insert(&h003);
    housesAdjToHouse2.insert(&h006);
    housesAdjToHouse2.insert(&h007);
    housesAdjToHouse2.insert(&h008);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h005);
    housesAdjToHouse11.insert(&h006);
    housesAdjToHouse11.insert(&h007);
    housesAdjToHouse11.insert(&h010);
    housesAdjToHouse11.insert(&h012);
    housesAdjToHouse11.insert(&h015);
    housesAdjToHouse11.insert(&h016);
    housesAdjToHouse11.insert(&h017);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h006);
    housesAdjToHouse12.insert(&h007);
    housesAdjToHouse12.insert(&h008);
    housesAdjToHouse12.insert(&h011);
    housesAdjToHouse12.insert(&h013);
    housesAdjToHouse12.insert(&h016);
    housesAdjToHouse12.insert(&h017);
    housesAdjToHouse12.insert(&h018);

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
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7,&greenNeighbor0001));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor0002));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor0001));
    
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

TEST_CASE("Resident_Falling findBestHome()"
    " blue resident has choice of a) two green neigbors, b) one green plus"
    " one blue residents, c) two green and one blue residents"
    " chooses either a).")
{   std::cout << "testResident rising findHouse() "<< std::endl;
    Resident_Rising blueResident{ 
        1, 
        1, 
        0.0,  // allowed movement
        0.6, // happiness Goal
        0.0,  // happinessValueAtZeroDiversity
        1.0,  // happinessValueAtOneDiversity
    };

    House& oldHouse = h000;  // resident's current house
    House& grHouse7 = h007;   // green resident lives in house 7
    House& grHouse8 = h008;   // green resident lives in house 8
    House& blHouse16 = h016;  // blue resident lives in house 16
    House& house2  = h002; // next to two green residents (happiness = 1.0)
    House& house11 = h011; // next to one green + one blue residents (happiness = 0.5)
    House& house12 = h012; // next to two green + one blue residents (happiness = 0.66)

    std::set<House*> housesAdjToHouse2;
    housesAdjToHouse2.insert(&h001);
    housesAdjToHouse2.insert(&h003);
    housesAdjToHouse2.insert(&h006);
    housesAdjToHouse2.insert(&h007);
    housesAdjToHouse2.insert(&h008);

    std::set<House*> housesAdjToHouse11;
    housesAdjToHouse11.insert(&h005);
    housesAdjToHouse11.insert(&h006);
    housesAdjToHouse11.insert(&h007);
    housesAdjToHouse11.insert(&h010);
    housesAdjToHouse11.insert(&h012);
    housesAdjToHouse11.insert(&h015);
    housesAdjToHouse11.insert(&h016);
    housesAdjToHouse11.insert(&h017);

    std::set<House*> housesAdjToHouse12;
    housesAdjToHouse12.insert(&h006);
    housesAdjToHouse12.insert(&h007);
    housesAdjToHouse12.insert(&h008);
    housesAdjToHouse12.insert(&h011);
    housesAdjToHouse12.insert(&h013);
    housesAdjToHouse12.insert(&h016);
    housesAdjToHouse12.insert(&h017);
    housesAdjToHouse12.insert(&h018);

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
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse7,&greenNeighbor0001));
    houseToResMap.insert(std::pair<House*, Resident*>(&grHouse8,&greenNeighbor0002));
    houseToResMap.insert(std::pair<House*, Resident*>(&blHouse16, &blueNeighbor0001));
    
    House* answerHouse = blueResident.findBestHome(
            &oldHouse,
            openHousesAndTheirAdjHouses,
            houseToResMap
        );
    
    REQUIRE((
        answerHouse == &house2
    ));

}