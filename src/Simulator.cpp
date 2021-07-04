#include "Simulator.h"
#include <algorithm>

Simulator::Simulator (City* city, std::vector<Resident*> residents):
    _city{city}, _residents{residents}{}

std::map<int, Resident*> Simulator::simulate()
{
    if (!firstSimDone)
    {
        firstSimulation();
        firstSimDone = true;
        return _curr_addr_to_res_map;
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
    std::map<Resident*, int> ResToOldAddressMapForForcedRes = 
        getAddresses(forcedMoveResidents);
    // all forcedMoveResidents' houses are available to move into.
    openHouses(forcedMoveResidents);
    std::set<int> occupied = getKeysFromMap(_curr_addr_to_res_map);

    while ( forcedResIt != forcedResIdxs.end() ||
        optionalResIt != optionalResIdxs.end()
    )
    {   
        if (forcedResIt != forcedResIdxs.end())
        {   
            Resident* curr = _residents[*forcedResIt];
            int oldAddress = ResToOldAddressMapForForcedRes[curr];
            std::set<int> openHouses = _city->getCloseAddresses(
                oldAddress,
                100,
                occupied,
                chances
            );

            int newAddress = -1;
            if (curr->getHappyAtGoal())
            { 
                newAddress = findAddressForForcedResHappyAtGoal(
                    curr,
                    oldAddress,
                    openHouses
                );
            }
            else // happyAtGoal = false; Then find the best house
            { 
                newAddress = findAddressForForcedResHappyAtBest(
                    curr,
                    oldAddress,
                    openHouses
                );
            }
            _curr_addr_to_res_map.insert(std::pair<int, Resident*>(
                newAddress,
                curr
            ));
            
            ++forcedResIt;
        }
        if (optionalResIt != optionalResIdxs.end())
        { 
            Resident* curr = _residents[*optionalResIt];
            int oldHouse = ResToOldAddressMapForForcedRes[curr];
            int tries = chances;
            std::set<int> openHouses = filterForOpenHouses(
                _city->getCloseAddresses(
                    ResToOldAddressMapForForcedRes[curr],
                    25
                )
            );
            int newAddress = findAddressForOptionalMoveRes(
                curr,
                oldHouse,
                openHouses,
                tries
            );
            _curr_addr_to_res_map.insert(std::pair<int, Resident*>(
                newAddress,
                curr
            ));
            ++optionalResIt;
            
        }
    }
        
    return _curr_addr_to_res_map;
}

std::set<int> Simulator::getKeysFromMap (std::map<int, Resident*> theMap)
{
    std::set<int> keysToReturn;
    for (std::map<int, Resident*>::iterator it = theMap.begin(); it != theMap.end(); ++it)
    {
        keysToReturn.insert(it->first);
    }
    return keysToReturn;
}

int Simulator::selectRandom(std::set<int>& setOfInt) const
{   int size = setOfInt.size();
    int r = rand() % size;
    std::set<int>::iterator it = std::begin(setOfInt);
    std::advance(it, r);
    setOfInt.erase(*it);
    return *it;
}

void Simulator::firstSimulation()
{
    std::set<int> openAddresses = getSetOfAddresses();
    
    for (Resident* res : _residents)
    {
        int address = selectRandom(openAddresses);
        _curr_addr_to_res_map.insert({address, res});
    }
}

std::set<int> Simulator::getSetOfAddresses()
{
    std::vector<int> addresses = _city->getAddresses();
    std::set<int> openAddresses;
    for (int address : addresses)
    {
        openAddresses.insert(address);
    }
    return openAddresses;
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
    std::map<Resident*, int> currResidentToAddressMap = {};
    for (auto const& m : _curr_addr_to_res_map)
    {
        currResidentToAddressMap.insert(std::pair<Resident*, int>(
            m.second,
            m.first
        ));
    }
    for (Resident* res :residents)
    {
        _curr_addr_to_res_map.erase(currResidentToAddressMap[res]);
    }
}

std::map<Resident*, int> Simulator::getAddresses (std::vector<Resident*> residents)
{
    std::map<Resident*, int> resToAddrMap = {};
    for (auto const& m : _curr_addr_to_res_map)
    {
        resToAddrMap.insert(std::pair<Resident*, int>(
            m.second,
            m.first
        ));
    }
    std::map<Resident*, int> selectResToAddrMap = {};
    for ( Resident* res : residents)
    {
        selectResToAddrMap.insert(std::pair<Resident*, int>(
            res,
            resToAddrMap[res]
        ));
    }
    return selectResToAddrMap;
} 

std::set<int> Simulator::filterForOpenHouses (std::set<int> addresses)
{
    std::set<int> openHouses;
    for (int addr : addresses)
    {
        if (_curr_addr_to_res_map.count(addr) != 0)
        {
            openHouses.insert(addr);
        }
    }
    return openHouses;
}

// TODO not used probably delete
int Simulator::findAddressForForcedRes (
    Resident* res,
    int oldAddress,
    std::set<int> openHouses, // open houses within distance of resident
    int chances
)
{   (void) chances;
    if (res->getHappyAtGoal())
    { 
        return findAddressForForcedResHappyAtGoal(
            res,
            oldAddress,
            openHouses // TODO tries should be taken into account
        );
    }
    else
    { 
        return findAddressForForcedResHappyAtBest (
            res,
            oldAddress,
            openHouses
        );
    }
}

int Simulator::findAddressForOptionalMoveRes (
        Resident* res,
        int oldAddress,
        std::set<int> openHouses, // open houses within distance of resident
        int chances
    )
{
    openHouses.erase(oldAddress);
    
    std::vector<int> adjacentAddresses = _city->getAdjacentAdresses(oldAddress);
    std::vector<Color> adjacentColors = getColors(adjacentAddresses);
    double oldAddressHappinesss = res->getHappiness(
        adjacentColors,
        adjacentAddresses.size()
    );
    double highHappiness = oldAddressHappinesss;

    std::map<double, int> happinessToAddrMap = {};
    for (int address : openHouses)
    {  
        if (chances == 0)
            break;
        std::vector<int> adjacentAddresses = _city->getAdjacentAdresses(address);
        std::vector<Color> adjacentColors = getColors(adjacentAddresses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentAddresses.size()
        );
        highHappiness = happiness > highHappiness ? happiness : highHappiness;
        happinessToAddrMap.insert(
            std::pair<double, int>(happiness, address)
        );
        --chances;
    }

    if (highHappiness > oldAddressHappinesss)
        return happinessToAddrMap[highHappiness];

    return oldAddress;
}

// If @openHouses is empty (or only contains the @oldAddress), returns @oldAddress.
// @oldAddress is removed from @openHouses.
// Goes through openHouses until a house that meets the happinessGoal is found.
// Returns that address.
// If no house is found that meets happinessGoal, returns house that makes
// resident most happy.
int Simulator::findAddressForForcedResHappyAtGoal (
    Resident* res,
    int oldAddress,
    std::set<int> openHouses
)
{
    // old address is not a possibility. Resident must move.
    if (openHouses.count(oldAddress) != 0)
        openHouses.erase(oldAddress); 
    double highHappiness = -1; // most happiness seen so far, will be updated
    int happiestAddress = oldAddress;

    for (int address : openHouses)
    {
        std::vector<int> adjacentAddresses = _city->getAdjacentAdresses(address);
        std::vector<Color> adjacentColors = getColors(adjacentAddresses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentAddresses.size()
        );
        if (happiness >= res->getHappinessGoal())
            return address;
        if (happiness > highHappiness)
        {
            highHappiness = happiness;
            happiestAddress = address;
        }
    }
    return happiestAddress;
}

// If @openHouses is empty (or only contains the @oldAddress), returns @oldAddress.
// @oldAddress is removed from @openHouses.
// Goes through openHouses, recording the address that makes resident happiest.
// Returns the happiest address.
int Simulator::findAddressForForcedResHappyAtBest (
    Resident* res,
    int oldAddress,
    std::set<int> openHouses
)
{
    // old address is not a possibility. Resident must move.
    if (openHouses.count(oldAddress) != 0)
        openHouses.erase(oldAddress); 
    double highHappiness = -1; // most happiness seen so far, will be updated
    int happiestAddress = oldAddress;

    for (int address : openHouses)
    {
        std::vector<int> adjacentAddresses = _city->getAdjacentAdresses(address);
        std::vector<Color> adjacentColors = getColors(adjacentAddresses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentAddresses.size()
        );
        if (happiness > highHappiness)
        {
            highHappiness = happiness;
            happiestAddress = address;
        }
    }
    return happiestAddress;
}

std::vector<Color> Simulator::getColors (std::vector<int> addresses)
{
    std::vector<Color> colors;
    for (int address : addresses)
    {
        if (_curr_addr_to_res_map.count(address) != 0)
        {
            colors.push_back(
                (_curr_addr_to_res_map[address])->getColor()
            );
        }
    }
    return colors;
}