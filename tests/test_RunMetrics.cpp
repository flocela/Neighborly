#include "catch.hpp"
#include "../src/RunMetrics.h"

#include <memory>
#include "../src/City_Grid.h"
#include "../src/HappinessFunc_StepDown.h"
#include "../src/Resident_UsingFunction.h"

using namespace std;

vector<Resident*> createResidents (int numOfResidents, int groupId, int firstId)
{   
    vector<Resident*> residents{};
    for (int ii=firstId; ii<numOfResidents+firstId; ++ii)
    {
        residents.push_back(new Resident_UsingFunction(
        ii,
        groupId,
        2.2,
        .5,
        make_unique<HappinessFunc_StepDown>(
            80,  // happinessWithZeroNeighbors
            100, // happinessAtZeroDiversity
            20,  // happinessAt100%Diversity
            .5   // step-down location
        )));
    }
    return residents;
}

unordered_set<const Resident*> createResidentsSet (int numOfResidents, int groupId, int firstId)
{   
    unordered_set<const Resident*> residents{};
    for (int ii=firstId; ii<numOfResidents+firstId; ++ii)
    {
        residents.insert(new Resident_UsingFunction(
        ii,
        groupId,
        2.2,
        1.0,
        make_unique<HappinessFunc_StepDown>(
            80,  // happinessWithZeroNeighbors
            100, // happinessAtZeroDiversity
            20,  // happinessAt100%Diversity
            .5   // step-down location
        )));
    }
    return residents;
}

unordered_map<const House*, unordered_set<const House*>> getAdjacentHousesPerHouse(const City* city)
{
    vector<const House*> houses = city->getHouses();
    unordered_map<const House*, unordered_set<const House*>> adjacentHousesPerHouse{};
    for (const House* house : houses)
    {   
        adjacentHousesPerHouse[house] = city->getHousesAdjacent(house->getAddress());
    }

    return adjacentHousesPerHouse;
}

TEST_CASE("empty city")
{
    City_Grid city = City_Grid(20);
    RunMetrics rm{getAdjacentHousesPerHouse(&city), "simA"};
    unordered_map<const House*, const Resident*> residentsPerHouse{};
    unordered_map<int, int> numOfResidentsPerGroupId{};
    unordered_map<int, int> numOfDiffNeighborsPerGroupId{};
    unordered_map<int, double> happinessSumPerGroupId{};
    unordered_map<int, const Resident*> residentExamplePerGroupId{};

    REQUIRE(residentsPerHouse == rm.getResidentsPerHouse());
    REQUIRE(numOfResidentsPerGroupId == rm.getNumOfResidentsPerGroupId());
    REQUIRE(numOfDiffNeighborsPerGroupId == rm.getNumOfDiffNeighborsPerGroupId());
    REQUIRE(happinessSumPerGroupId == rm.getHappinessSumPerGroupId());
    REQUIRE(residentExamplePerGroupId == rm.getResidentExamplePerGroupId());
}
// 20 x 20 grid, three columns of group1
// row x col:
// group1 column from (5, 5) to (14, 5)
// group1 column from (5, 6) to (14, 6)
// group1 column from (5, 7) to (14, 7)

TEST_CASE("three columns of group1")
{
    City_Grid city = City_Grid(20);
    vector<const House*> cityHouses = city.getHouses();

    int numOfResidents = 30;
    int groupNum = 1;
    int startId = 0;
    vector<Resident*> group1Residents = createResidents(
        numOfResidents,
        groupNum,
        startId
    );

    // Used for setting resident's happiness
    unordered_set<const Resident*> group1Set = createResidentsSet(1, 1, 0);

    unordered_map<const House*, const Resident*> residentsPerHouse{};
    int resCounter = 0;
    for (int col=5; col<=7; ++col)
    {
        for (int row=5; row<=14; ++row)
        {
            int address = row*20 + col;
            residentsPerHouse.insert({cityHouses[address], group1Residents[resCounter]});
            group1Residents[resCounter]->setHappiness(group1Set, 1);
            ++resCounter;
        }
    }

    RunMetrics rm{getAdjacentHousesPerHouse(&city), "simA"};
    rm.updateMetrics(1, residentsPerHouse);

    REQUIRE(residentsPerHouse == rm.getResidentsPerHouse());
    REQUIRE(numOfResidents == rm.getNumOfResidentsPerGroupId()[1]);
    REQUIRE(0 == rm.getNumOfDiffNeighborsPerGroupId()[1]);
    REQUIRE(3000 == rm.getHappinessSumPerGroupId()[1]);
    REQUIRE(1 == rm.getResidentExamplePerGroupId()[1]->getGroupId());
}

// 20 x 20 grid, three columns of group1
// row x col:
// group1 column from (5, 5) to (14, 5) -> labeled as A
// group1 column from (5, 6) to (14, 6) -> labeled as A
// group1 column from (5, 7) to (14, 7) -> labeled as A
// group2 column from (5, 8) to (14, 8) -> labeled as B
// group1 column from (5, 9) to (14, 9) -> labeled as C
// group2 column from (5, 10) to (14, 10) -> labeled as D
TEST_CASE("four columns of group1, two columns of group2")
{
    City_Grid city = City_Grid(20);
    vector<const House*> cityHouses = city.getHouses();
    unordered_map<const House*, const Resident*> residentsPerHouse{};

    // Used for setting resident's happiness
    unordered_set<const Resident*> group1Set = createResidentsSet(1, 1, 0);
    unordered_set<const Resident*> group2Set = createResidentsSet(1, 2, 0);

    int numOfResidentsA = 30;
    int groupNumA = 1;
    int startIdA = 0;
    vector<Resident*> groupA = createResidents(
        numOfResidentsA,
        groupNumA,
        startIdA
    );

    int resCounter = 0;
    for (int col=5; col<=7; ++col)
    {
        for (int row=5; row<=14; ++row)
        {
            int address = row*20 + col;
            residentsPerHouse.insert({cityHouses[address], groupA[resCounter]});
            // all groupA residents have happiness of 100
            groupA[resCounter]->setHappiness(group1Set, 1);
            ++resCounter;
        }
    }

    resCounter = 0;
    int numOfResidentsB = 10;
    int groupNumB = 2;
    int startIdB = 30;
    vector<Resident*> groupB = createResidents(
        numOfResidentsB,
        groupNumB,
        startIdB
    );

    for (int col=8; col<=8; ++col)
    {
        for (int row=5; row<=14; ++row)
        {
            int address = row*20 + col;
            residentsPerHouse.insert({cityHouses[address], groupB[resCounter]});
            // all groupB residents have lower happiness value
            groupB[resCounter]->setHappiness(group1Set, 1);
            ++resCounter;
        }
    }

    resCounter = 0;
    int numOfResidentsC = 10;
    int groupNumC = 1;
    int startIdC = 40;
    vector<Resident*> groupC = createResidents(
        numOfResidentsC,
        groupNumC,
        startIdC
    );

    for (int col=9; col<=9; ++col)
    {
        for (int row=5; row<=14; ++row)
        {
            int address = row*20 + col;
            residentsPerHouse.insert({cityHouses[address], groupC[resCounter]});
            // top two and bottom two rows have lower happiness value
            if (row == 5 || row == 6 || row == 13 || row == 14)
            {
                groupC[resCounter]->setHappiness(group2Set, 1);
            }
            else
            {
                groupC[resCounter]->setHappiness(group1Set, 1);
            }
            ++resCounter;
        }
    }

    resCounter = 0;
    int numOfResidentsD = 10;
    int groupNumD = 2;
    int startIdD = 50;
    vector<Resident*> groupD = createResidents(
        numOfResidentsD,
        groupNumD,
        startIdD
    );

    for (int col=10; col<=10; ++col)
    {
        for (int row=5; row<=14; ++row)
        {
            int address = row*20 + col;
            residentsPerHouse.insert({cityHouses[address], groupD[resCounter]});
            // all groupD residents have lower happiness value
            groupD[resCounter]->setHappiness(group1Set, 1);
            ++resCounter;
        }
    }

    RunMetrics rm{getAdjacentHousesPerHouse(&city), "simA"};
    rm.updateMetrics(1, residentsPerHouse);

    REQUIRE(residentsPerHouse == rm.getResidentsPerHouse());
    REQUIRE(40 == rm.getNumOfResidentsPerGroupId()[1]);
    REQUIRE(20 == rm.getNumOfResidentsPerGroupId()[2]);

    // group1 disparate neighbors:
    //    groupA's 3rd column has 8X3 + 2X2
    //    groupC's column has 8X6 + 2X4
    //    total is 84
    REQUIRE(84 == rm.getNumOfDiffNeighborsPerGroupId()[1]);

    // group2 disparate neighbors:
    //    groupB's column has 8X6 + 2X4
    //    groupD's column has 8X3 + 2X2
    //    total is 84
    REQUIRE(84 == rm.getNumOfDiffNeighborsPerGroupId()[1]);

    // group1 happinessSum:
    //    groupA's is is 30X100
    //    groupC's is is 4X20 + 6X100
    //    total is 3680
    REQUIRE(3680 == rm.getHappinessSumPerGroupId()[1]);

    // group2 happinessSum:
    //    groupB's is is 10X20
    //    groupD's is is 10X20
    //    total is 400
    REQUIRE(400 == rm.getHappinessSumPerGroupId()[2]);

    REQUIRE(1 == rm.getResidentExamplePerGroupId()[1]->getGroupId());
    REQUIRE(2 == rm.getResidentExamplePerGroupId()[2]->getGroupId());
}
