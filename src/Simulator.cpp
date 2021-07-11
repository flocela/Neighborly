#include "Simulator.h"
#include <algorithm>

Simulator::Simulator (City* city, std::vector<Resident*> residents):
    _city{city}, _residents{residents}{}

std::map<House*, Resident*> Simulator::simulate()
{
    if (!firstSimDone)
    {
        firstSimulation();
        firstSimDone = true;
        return _curr_house_to_res_map;
    }
    int chances = 2;
    // forcedResIdxs hold indexes corresponding to residents in _residents.
    // optionalResIdxs hold the indexes corresponding to residents in _residents.
    // forcedResIdxs are residents that are forced to move.
    // optionalResIdxs are residents that can choose not to move.
    // forcedResIdxs and optionalResIdxs have integers in random order.
    // Each iteration of while loop will designate a house for a resident in
    // forcedResIdxs and then designate a house for a resident in optionalResIdxs.
    std::pair<std::vector<int>, std::vector<int>> moving = getMovingResIdxs();
    std::vector<int> forcedResIdxs = moving.first;
    std::vector<int> optionalResIdxs = moving.second;
    std::vector<int>::iterator forcedResIt = forcedResIdxs.begin();
    std::vector<int>::iterator optionalResIt = optionalResIdxs.begin();

    std::vector<Resident*> forcedMoveResidents = getResidents(forcedResIdxs);
    std::map<Resident*, House*> resToOldHouseMapForForcedRes = 
        getHouses(forcedMoveResidents);
    // call openHouses() so that all forcedMoveResidents' houses are available
    // to move into.
    openHouses(forcedMoveResidents);
    while ( forcedResIt != forcedResIdxs.end() ||
        optionalResIt != optionalResIdxs.end()
    )
    {   
        if (forcedResIt != forcedResIdxs.end())
        {   
            Resident* curr = _residents[*forcedResIt];
            House* newHouse = findHomeForForcedToMoveResident(
                curr,
                resToOldHouseMapForForcedRes[curr],
                chances
            );
            moveResidentIntoHouse(curr, newHouse);
            ++forcedResIt;
        }
        if (optionalResIt != optionalResIdxs.end())
        { 
            Resident* curr = _residents[*optionalResIt];
            House* oldHouse = _curr_res_to_house_map[curr];
            std::set<House*> closeOpenHouses = filterForOpenHouses(
                _city->getNearHouses(
                    oldHouse,
                    25
                )
            );
            // TODO what if openHouses is empty?
            House* newHouse = curr->findHome(
                _city,
                oldHouse,
                closeOpenHouses,
                _curr_house_to_res_map
            );
            moveResidentIntoHouse(curr, newHouse);
            
            ++optionalResIt;
            
        }
    }
       
    return _curr_house_to_res_map;
}

std::set<House*> Simulator::getKeysFromMap (std::map<House*, Resident*> theMap)
{
    std::set<House*> keysToReturn;
    for (std::map<House*, Resident*>::iterator it = theMap.begin(); it != theMap.end(); ++it)
    {
        keysToReturn.insert(it->first);
    }
    return keysToReturn;
}

House* Simulator::selectRandom(std::set<House*>& setOfHouses) const
{   
    int size = setOfHouses.size();
    int r = rand() % size;
    std::set<House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
    setOfHouses.erase(*it);
    return *it; // TODO this isn't going to work because I erase it first!!
}

int Simulator::selectRandom(std::set<int>& setOfInts) const
{   
    int size = setOfInts.size();
    int r = rand() % size;
    std::set<int>::iterator it = std::begin(setOfInts);
    std::advance(it, r);
    setOfInts.erase(*it);
    return *it; // TODO this isn't going to work because I erase it first!!
}

void Simulator::firstSimulation()
{
    std::set<House*> openHouses = getSetOfHouses();
    
    for (Resident* res : _residents)
    {
        House* house = selectRandom(openHouses);
        moveResidentIntoHouse(res, house);
    }
}

std::set<House*> Simulator::getSetOfHouses()
{
    std::vector<House*> houses = _city->getHouses();
    std::set<House*> openHouses;
    for (House* house : houses)
    {
        openHouses.insert(house);
    }
    return openHouses;
}

std::set<int> Simulator::getSetOfInts(int max)
{
    std::set<int> ints;
    for (int ii=0; ii<max; ii++)
    {
        ints.insert(ii);
    }
    return ints;
}

std::pair<std::vector<int>, std::vector<int>> Simulator::getMovingResIdxs()
{
    std::set<int> residentIdxsSet = getSetOfInts(_residents.size());
    std::vector<int> forcedResidentIndices;
    std::vector<int> optionalResidentIndices;
    // chosen is total number of residents that are chosen.
    // At each iteration, one is chosen for being forced
    // to move and one is chosen that can optionally move.
    int chosen = _residents.size() * 0.2;
    for (int ii=0; ii<chosen/2; ii++)
    {
        int chosenIdx = selectRandom(residentIdxsSet);
        forcedResidentIndices.push_back(chosenIdx);

        chosenIdx = selectRandom(residentIdxsSet);
        optionalResidentIndices.push_back(chosenIdx);
    }
    return std::pair<std::vector<int>, std::vector<int>>{
        forcedResidentIndices, 
        optionalResidentIndices
    };
}

std::vector<Resident*> Simulator::getResidents(
   std::vector<int> residentIndices)
{
    std::vector<Resident*> moving;
    for (int index : residentIndices)
    {
        moving.push_back(_residents[index]);
    }
    return moving;
}

void Simulator::openHouses(std::vector<Resident*> residents){
    for (Resident* res :residents)
    {
        openHouse(res);
    }
}

std::map<Resident*, House*> Simulator::getHouses (std::vector<Resident*> residents)
{
    std::map<Resident*, House*> selectResToAddrMap = {};
    for ( Resident* res : residents)
    {   
        selectResToAddrMap.insert(std::pair<Resident*, House*>(
            res,
            _curr_res_to_house_map[res]
        ));
    }
    return selectResToAddrMap;
} 

std::set<House*> Simulator::filterForOpenHouses (std::set<House*> houses)
{
    std::set<House*> openHouses;
    for (House* house : houses)
    {
        if (_curr_house_to_res_map.count(house) != 0)
        {
            openHouses.insert(house);
        }
    }
    return openHouses;
}

House* Simulator::findHouseForOptionalMoveRes (
        Resident* res,
        House* oldHouse,
        std::set<House*> openHouses, // open houses within distance of resident
        int chances
)
{
    openHouses.erase(oldHouse);
    
    std::vector<House*> adjacentHouses = _city->getAdjacentHouses(oldHouse);
    std::vector<Color> adjacentColors = getColors(adjacentHouses);
    double oldAddressHappinesss = res->getHappiness(
        adjacentColors,
        adjacentHouses.size()
    );
    double highHappiness = oldAddressHappinesss;

    std::map<double, House*> happinessToHouseMap = {};
    for (House* house : openHouses)
    {  
        if (chances == 0)
            break;
        std::vector<House*> adjacentHouses = _city->getAdjacentHouses(house);
        std::vector<Color> adjacentColors = getColors(adjacentHouses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentHouses.size()
        );
        highHappiness = happiness > highHappiness ? happiness : highHappiness;
        happinessToHouseMap.insert(
            std::pair<double, House*>(happiness, house)
        );
        --chances;
    }

    if (highHappiness > oldAddressHappinesss)
        return happinessToHouseMap[highHappiness];

    return oldHouse;
}

// If @openHouses is empty (or only contains the @oldAddress), returns @oldAddress.
// @oldAddress is removed from @openHouses.
// Goes through openHouses until a house that meets the happinessGoal is found.
// Returns that address.
// If no house is found that meets happinessGoal, returns house that makes
// resident most happy.
House* Simulator::findHouseForForcedResHappyAtGoal (
    Resident* res,
    House* oldHouse,
    std::set<House*> openHouses
)
{
    // old address is not a possibility. Resident must move.
    if (openHouses.count(oldHouse) != 0)
        openHouses.erase(oldHouse); 
    double highHappiness = -1; // most happiness seen so far, will be updated
    House* happiestHouse = oldHouse;

    for (House* house : openHouses)
    {
        std::vector<House*> adjacentAddresses = _city->getAdjacentHouses(house);
        std::vector<Color> adjacentColors = getColors(adjacentAddresses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentAddresses.size()
        );
        if (happiness >= res->getHappinessGoal())
            return house;
        if (happiness > highHappiness)
        {
            highHappiness = happiness;
            happiestHouse = house;
        }
    }
    return happiestHouse;
}

// If @openHouses is empty (or only contains the @oldAddress), returns @oldAddress.
// @oldAddress is removed from @openHouses.
// Goes through openHouses, recording the address that makes resident happiest.
// Returns the happiest address.
House* Simulator::findHouseForForcedResHappyAtBest (
    Resident* res,
    House* oldHouse,
    std::set<House*> openHouses
)
{
    // old address is not a possibility. Resident must move.
    if (openHouses.count(oldHouse) != 0)
        openHouses.erase(oldHouse); 
    double highHappiness = -1; // most happiness seen so far, will be updated
    House* happiestHouse = oldHouse;

    for (House* house : openHouses)
    {
        std::vector<House*> adjacentHouses = _city->getAdjacentHouses(house);
        std::vector<Color> adjacentColors = getColors(adjacentHouses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentHouses.size()
        );
        if (happiness > highHappiness)
        {
            highHappiness = happiness;
            happiestHouse = house;
        }
    }
    return happiestHouse;
}

std::vector<Color> Simulator::getColors (std::vector<House*> houses)
{
    std::vector<Color> colors;
    for (House* house : houses)
    {
        if (_curr_house_to_res_map.count(house) != 0)
        {
            colors.push_back(
                (_curr_house_to_res_map[house])->getColor()
            );
        }
    }
    return colors;
}

House* Simulator::findHomeForForcedToMoveResident (
    Resident* resident,
    House* oldHouse,
    int count
)
{
    std::set<House*> occupied = getKeysFromMap(_curr_house_to_res_map);
    std::set<House*> nearOpenHouses = _city->getNearHouses(
        oldHouse,
        100,
        occupied,
        count
    );
    //TODO if closeOpenHouses is empty.
    House* newHome = resident->findHome(
        _city,
        oldHouse,
        nearOpenHouses,
        _curr_house_to_res_map
    );
    
    return newHome;
}

House* Simulator::findHomeForOptionalMoveResident (
    Resident* resident,
    House* oldHouse,
    int count
)
{
    std::set<House*> occupied = getKeysFromMap(_curr_house_to_res_map);
    std::set<House*> nearOpenHouses = _city->getNearHouses(
        oldHouse,
        100,
        occupied,
        count
    );
    //TODO if closeOpenHouses is empty.

    House* newHouse = resident->findBestHome(
        _city,
        oldHouse,
        nearOpenHouses,
        _curr_house_to_res_map
    );
    return newHouse;
}

void Simulator::moveResidentIntoHouse (Resident* res, House* house)
{
    House* oldHouse = _curr_res_to_house_map[res];
    _curr_house_to_res_map.erase(oldHouse);
    _curr_res_to_house_map.erase(res);
    _curr_house_to_res_map.insert(std::pair<House*, Resident*>(
        house,
        res
    ));
    _curr_res_to_house_map.insert(std::pair<Resident*, House*>(
        res,
        house
    ));
}

void Simulator::openHouse (Resident* res)
{
    House* house = _curr_res_to_house_map[res];
    _curr_res_to_house_map.erase(res);
    _curr_house_to_res_map.erase(house);
}