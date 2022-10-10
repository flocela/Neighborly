#include "Simulator_E.h"
#include <algorithm>

Simulator_E::Simulator_E (City* city, std::vector<Resident*> residents):
    _city{city}, _residents{residents}{}

std::unordered_map<const House*, Resident*> Simulator_E::simulate()
{   //(void) randomSeed;
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
    std::unordered_map<Resident*, const House*> resToOldHouseMapForForcedRes = 
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
            const House* newHouse = findHomeForForcedToMoveResident(
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
            const House* oldHouse = _curr_res_to_house_map[curr];
            std::unordered_set<House*> nearHouses;
            _city->getHousesWithinDistance(
                    oldHouse,
                    25,
                    nearHouses,
                    std::set<const House*>()
                );
            std::unordered_set<House*> nearOpenHouses = filterForOpenHouses(nearHouses);
            // TODO what if openHouses is empty?
            const House* newHouse = curr->findHome(
                oldHouse,
                getSetsOfNeighbors(nearOpenHouses),
                _curr_house_to_res_map
            );
            moveResidentIntoHouse(curr, newHouse);
            
            ++optionalResIt;
            
        }
    }
       
    return _curr_house_to_res_map;
}

std::set<const House*> Simulator_E::getKeysFromMap (std::unordered_map<const House*, Resident*> theMap)
{
    std::set<const House*> keysToReturn;
    for (auto hR : theMap)
    {
        keysToReturn.insert(hR.first);
    }
    return keysToReturn;
}

const House* Simulator_E::selectRandom(std::set<const House*>& setOfHouses) const
{   
    int size = setOfHouses.size();
    int r = rand() % size;
    std::set<const House*>::iterator it = std::begin(setOfHouses);
    std::advance(it, r);
    setOfHouses.erase(*it);
    return *it; // TODO this isn't going to work because I erase it first!!
}

int Simulator_E::selectRandom(std::set<int>& setOfInts) const
{   
    int size = setOfInts.size();
    int r = rand() % size;
    std::set<int>::iterator it = std::begin(setOfInts);
    std::advance(it, r);
    setOfInts.erase(*it);
    return *it; // TODO this isn't going to work because I erase it first!!
}

void Simulator_E::firstSimulation()
{
    std::set<const House*> openHouses = getSetOfHouses();
    
    for (Resident* res : _residents)
    {
        const House* house = selectRandom(openHouses);
        moveResidentIntoHouse(res, house);
    }
}

std::set<const House*> Simulator_E::getSetOfHouses()
{
    std::vector<const House*> houses = _city->getHouses();
    std::set<const House*> openHouses;
    for (const House* house : houses)
    {
        openHouses.insert(house);
    }
    return openHouses;
}

std::set<int> Simulator_E::getSetOfInts(int max)
{
    std::set<int> ints;
    for (int ii=0; ii<max; ii++)
    {
        ints.insert(ii);
    }
    return ints;
}

std::pair<std::vector<int>, std::vector<int>> Simulator_E::getMovingResIdxs()
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

std::vector<Resident*> Simulator_E::getResidents(
   std::vector<int> residentIndices)
{
    std::vector<Resident*> moving;
    for (int index : residentIndices)
    {
        moving.push_back(_residents[index]);
    }
    return moving;
}

void Simulator_E::openHouses(std::vector<Resident*> residents){
    for (Resident* res :residents)
    {
        openHouse(res);
    }
}

std::unordered_map<Resident*, const House*> Simulator_E::getHouses (std::vector<Resident*> residents)
{
    std::unordered_map<Resident*, const House*> selectResToAddrMap = {};
    for ( Resident* res : residents)
    {   
        selectResToAddrMap.insert(std::pair<Resident*, const House*>(
            res,
            _curr_res_to_house_map[res]
        ));
    }
    return selectResToAddrMap;
} 

std::unordered_set<House*> Simulator_E::filterForOpenHouses (std::unordered_set<House*> houses)
{
    std::unordered_set<House*> openHouses;
    for (House* house : houses)
    {
        if (_curr_house_to_res_map.count(house) != 0)
        {
            openHouses.insert(house);
        }
    }
    return openHouses;
}

House* Simulator_E::findHouseForOptionalMoveRes (
        Resident* res,
        House* oldHouse,
        std::set<House*> openHouses, // open houses within distance of resident
        int chances
)
{
    openHouses.erase(oldHouse);
    
    std::set<const House*> adjacentHouses = _city->getAdjacentHouses(oldHouse->getAddress());
    std::set<Resident*> adjacentResidents = getResidentsInHouses(adjacentHouses);
    double oldAddressHappinesss = res->getHappiness();
    double highHappiness = oldAddressHappinesss;

    std::map<double, House*> happinessToHouseMap = {};
    for (House* house : openHouses)
    {  
        if (chances == 0)
            break;
        std::set<const House*> adjacentHouses = _city->getAdjacentHouses(house->getAddress());
        std::set<Resident*> adjacentResidents = getResidentsInHouses(adjacentHouses);
        double happiness = res->getHappiness();
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
const House* Simulator_E::findHouseForForcedResHappyAtGoal (
    Resident* res,
    House* oldHouse,
    std::set<const House*> openHouses
)
{
    // old address is not a possibility. Resident must move.
    if (openHouses.count(oldHouse) != 0)
        openHouses.erase(oldHouse); 
    double highHappiness = -1; // most happiness seen so far, will be updated
    const House* happiestHouse = oldHouse;

    for (const House* house : openHouses)
    {
        std::set<const House*> adjacentHouses = _city->getAdjacentHouses(house->getAddress());
        std::set<Resident*> adjacentResidents = getResidentsInHouses(adjacentHouses);
        double happiness = res->getHappiness();
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
House* Simulator_E::findHouseForForcedResHappyAtBest (
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
        std::set<const House*> adjacentHouses = _city->getAdjacentHouses(house->getAddress());
        std::set<Resident*> adjacentResidents = getResidentsInHouses(adjacentHouses);
        double happiness = res->getHappiness();
        if (happiness > highHappiness)
        {
            highHappiness = happiness;
            happiestHouse = house;
        }
    }
    return happiestHouse;
}

const House* Simulator_E::findHomeForForcedToMoveResident (
    Resident* resident,
    const House* oldHouse,
    int count
)
{   (void) count;
    std::set<const House*> occupied = getKeysFromMap(_curr_house_to_res_map);
    std::unordered_set<House*> nearOpenHouses;
     _city->getHousesWithinDistance(
        oldHouse,
        100,
        nearOpenHouses,
        std::set<const House*>()
    );
    //TODO if closeOpenHouses is empty.
    const House* newHome = resident->findHome(
        oldHouse,
        getSetsOfNeighbors(nearOpenHouses),
        _curr_house_to_res_map
    );
    
    return newHome;
}

const House* Simulator_E::findHomeForOptionalMoveResident (
    Resident* resident,
    House* oldHouse,
    int count
)
{   (void) count;
    std::set<const House*> occupied = getKeysFromMap(_curr_house_to_res_map);

    std::unordered_set<House*> nearOpenHouses;
    _city->getHousesWithinDistance(
        oldHouse,
        100,
        nearOpenHouses,
        std::set<const House*>()
    );
    //TODO if closeOpenHouses is empty.
    const House* newHouse = resident->findBestHome(
        oldHouse,
        getSetsOfNeighbors(nearOpenHouses),
        _curr_house_to_res_map
    );
    return newHouse;
}

void Simulator_E::moveResidentIntoHouse (Resident* res, const House* house)
{
    const House* oldHouse = _curr_res_to_house_map[res];
    _curr_house_to_res_map.erase(oldHouse);
    _curr_res_to_house_map.erase(res);
    _curr_house_to_res_map.insert(std::pair<const House*, Resident*>(
        house,
        res
    ));
    _curr_res_to_house_map.insert(std::pair<Resident*, const House*>(
        res,
        house
    ));
}

void Simulator_E::openHouse (Resident* res)
{
    const House* house = _curr_res_to_house_map[res];
    _curr_res_to_house_map.erase(res);
    _curr_house_to_res_map.erase(house);
}

std::map<const House*, std::set<const House*>> Simulator_E::getSetsOfNeighbors (
    std::unordered_set<House*> houses
)
{
    std::map<const House*, std::set<const House*>> setsOfNeighbors;
    for (House* house : houses)
    {
        std::set<const House*> neighbors = _city->getAdjacentHouses(house->getAddress());
        setsOfNeighbors.insert(std::pair<House*, std::set<const House*>>(house, neighbors));
    }
    return setsOfNeighbors;
}

std::set<Resident*> Simulator_E::getResidentsInHouses (std::set<const House*> houses)
{  
    std::set<Resident*> residents{}; 
    for (const House* house : houses)
    {
        residents.insert(_curr_house_to_res_map[house]);
    }
    return residents;
}