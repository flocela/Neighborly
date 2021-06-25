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
    // ints in movingResidents are indices in _residents
    std::pair<std::vector<int>, std::vector<int>> moving = getMovingResIdxs();
    std::vector<Resident*> forcedMoveResidents = getResidents(moving.first);
    std::map<Resident*, int> resToOldAddrMap = getAddresses(forcedMoveResidents);
    openHouses(forcedMoveResidents);
    std::vector<int> forcedResIdxs = moving.first;
    std::vector<int> optionalResIdxs = moving.second;
    std::vector<int>::iterator forcedResIt = forcedResIdxs.begin();
    std::vector<int>::iterator optionalResIt = optionalResIdxs.begin();

    while ( forcedResIt != forcedResIdxs.end() ||
        optionalResIt != optionalResIdxs.end()
    )
    {
        if (forcedResIt != forcedResIdxs.end())
        {   
            Resident* curr = _residents[*forcedResIt];
            std::set<int> openHouses = getOnlyOpenHouses(
                _city->getAddressesWithin(
                    resToOldAddrMap[curr],
                    100
                )
            );
            int oldHouse = resToOldAddrMap[curr];
            openHouses.erase(oldHouse);
            std::map<double, int> happinessToAddress = {};
            int tries = chances;

            int newAddress = -1;
            if (curr->getHappyAtGoal())
            { 
                newAddress = findForcedAddressHappyAtGoal(
                    curr,
                    oldHouse,
                    openHouses,
                    tries
                );
            }
            else // happyAtGoal = false; Then find the best house
            { 
                newAddress = findForcedAddressHappyAtBest(
                    curr,
                    oldHouse,
                    openHouses,
                    tries
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
            int oldHouse = resToOldAddrMap[curr];
            int tries = chances;
            std::set<int> openHouses = getOnlyOpenHouses(
                _city->getAddressesWithin(
                    resToOldAddrMap[curr],
                    100
                )
            );
            int newAddress = findOptionalAddress(
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

std::set<int>::iterator Simulator::selectRandom(const std::set<int> &s, size_t n)
{
    std::set<int>::iterator it = std::begin(s);
    std::advance(it, n);
    return it;
}

void Simulator::firstSimulation()
{
    std::set<int> openAddresses = getSetOfAddresses();
    
    for (Resident* res : _residents)
    {
        int size = openAddresses.size();
        int r = rand() % size;
        int address = *selectRandom(openAddresses, r);
        _curr_addr_to_res_map.insert({address, res});
        openAddresses.erase(address);
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
    std::set<int> residentIndices = getSetOfInts(_residents.size());
    std::vector<int> forcedResidentIndices;
    std::vector<int> optionalResidentIndices;
    // choose is total number of times residents are choosen.
    int choose = _residents.size() * 0.2;
    for (int ii=0; ii<choose; ii++)
    {
        int size = residentIndices.size();
        int r = rand() % size;
        int chosenIdx = *selectRandom(residentIndices, r);
        if (ii % 2 == 0)
        {
            forcedResidentIndices.push_back(chosenIdx);
        }
        else
        {
            optionalResidentIndices.push_back(chosenIdx);
        }
        residentIndices.erase(chosenIdx);
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

std::set<int> Simulator::getOnlyOpenHouses (std::set<int> addresses)
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

int Simulator::findNewForcedAddress (
    Resident* res,
    int oldAddress,
    std::set<int> openHouses, // open houses within distance of resident
    int chances
)
{   
    if (res->getHappyAtGoal())
    { 
        return findForcedAddressHappyAtGoal(
            res,
            oldAddress,
            openHouses,
            chances
        );
    }
    else
    { 
        return findForcedAddressHappyAtBest (
            res,
            oldAddress,
            openHouses,
            chances
        );
    }
}

int Simulator::findOptionalAddress (
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

// TODO what if no address is found at all. Then allow to stay, maybe throw exception.
int Simulator::findForcedAddressHappyAtGoal (
    Resident* res,
    int oldAddress,
    std::set<int> openHouses, // open houses within distance of resident
    int chances
)
{
    openHouses.erase(oldAddress); // old address is not a possibility. Must move.
    double highHappiness = -1; // most happiness seen so far, will be updated
    std::map<double, int> happinessToAddress = {};
    int newAddress = oldAddress;
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
        happinessToAddress.insert(std::pair<double, int>(happiness, address));
        if (happiness >= res->getHappinessGoal())
            newAddress = address;
        else if (chances == 1)
            newAddress = happinessToAddress[highHappiness];
        --chances;
    }
    return newAddress;
}
// TODO what if no address is found at all. Then allow to stay, maybe throw exception.
int Simulator::findForcedAddressHappyAtBest (
    Resident* res,
    int oldAddress,
    std::set<int> openHouses, // open houses within distance of resident
    int chances
)
{
    openHouses.erase(oldAddress); // old address is not a possibility. Must move.
    double highHappiness = -1; // most happiness seen so far, will be updated
    std::map<double, int> happinessToAddress = {};
    for (int address : openHouses)
    {
        if (chances == 0)
            break;
        std::vector<int> adjacentAddresses =_city->getAdjacentAdresses(address);
        std::vector<Color> adjacentColors = getColors(adjacentAddresses);
        double happiness = res->getHappiness(
            adjacentColors,
            adjacentAddresses.size()
        );
        highHappiness = happiness > highHappiness ? happiness : highHappiness;
        happinessToAddress.insert(
            std::pair<double, int>(happiness, address)
        );
        --chances;
    }
    return happinessToAddress[highHappiness];
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