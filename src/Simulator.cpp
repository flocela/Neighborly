#include "Simulator.h"
#include <algorithm>

Simulator::Simulator (City* city, std::vector<Resident*> residents):
    _city{city}, _residents{residents}{}

std::map<int, Resident*> Simulator::simulate()
{
    int chances = 2;
    if ( _curr_addr_to_res_map.empty() )
    {
        firstSimulation();
        return _curr_addr_to_res_map;
    }
    // ints in movingResidents are indices in _residents
    std::pair<std::vector<int>, std::vector<int>> movingResidentIndices = 
        getMovingResidentIndices();
    std::vector<Resident*> forcedMoveResidents = 
        getMovingResidents(movingResidentIndices.first);
    std::map<Resident*, int> resToOldAddrMap = getOldAddresses(forcedMoveResidents);
    openHouses(forcedMoveResidents);
    std::vector<int> forcedResidentIdxs = movingResidentIndices.first;
    std::vector<int> optionalResidentsIdxs = movingResidentIndices.second;
    std::vector<int>::iterator forcedResIt = forcedResidentIdxs.begin();
    std::vector<int>::iterator optionalResIt = optionalResidentsIdxs.begin();
    int counter = std::max(
        forcedResidentIdxs.size(),
        optionalResidentsIdxs.size()
    );
    while ( counter != 0)
    {
        if (forcedResIt != forcedResidentIdxs.end())
        {   
            Resident* curr = _residents[*forcedResIt];
            std::set<int> possibleAddresses = _city->getAddressesWithin(
                resToOldAddrMap[curr],
                100
            );
            std::set<int> openHouses = getOnlyOpenHouses(possibleAddresses);
            int oldHouse = resToOldAddrMap[curr];
            openHouses.erase(oldHouse);
            std::map<double, int> happinessToAddress = {};
            double highHappiness = -1;
            int tries = chances;
            if (curr->getHappyAtGoal())
            { 
                for (int address : openHouses)
                {
                    if (tries == 0)
                        break;
                    std::vector<int> adjacentAddresses =
                        _city->getAdjacentAdresses(address);
                    std::vector<Color> adjacentColors;
                    for (int address : adjacentAddresses)
                    {
                        if (_curr_addr_to_res_map.count(address) != 0)
                        {
                            adjacentColors.push_back(
                                (_curr_addr_to_res_map[address])->getColor()
                            );
                        }
                    }
                    double happiness = curr->getHappiness(
                        adjacentColors,
                        adjacentAddresses.size()
                    );
                    highHappiness = happiness > highHappiness ? happiness : highHappiness;
                    happinessToAddress.insert(
                        std::pair<double, int>(happiness, address)
                    );
                    if (happiness >= curr->getHappinessGoal())
                    {
                       _curr_addr_to_res_map.insert(std::pair<int, Resident*>(
                           address,
                           curr
                        )); 
                        break;
                    }
                    else if (tries == 1)
                    {
                        _curr_addr_to_res_map.insert(std::pair<int, Resident*>(
                           happinessToAddress[highHappiness],
                           curr
                        ));
                    }
                    --tries;
                }
            }
            else // happyAtGoal = false; Then find the best house
            { 
                for (int address : openHouses)
                {
                    if (tries == 0)
                        break;
                    std::vector<int> adjacentAddresses =
                        _city->getAdjacentAdresses(address);
                    std::vector<Color> adjacentColors;
                    for (int address : adjacentAddresses)
                    {
                        if (_curr_addr_to_res_map.count(address) != 0)
                        {
                            adjacentColors.push_back(
                                (_curr_addr_to_res_map[address])->getColor()
                            );
                        }
                    }
                    double happiness = curr->getHappiness(
                        adjacentColors,
                        adjacentAddresses.size()
                    );
                    highHappiness = happiness > highHappiness ? happiness : highHappiness;
                    happinessToAddress.insert(
                        std::pair<double, int>(happiness, address)
                    );
                    --tries;
                }
                _curr_addr_to_res_map.insert(std::pair<int, Resident*>(
                    happinessToAddress[highHappiness],
                    curr
                ));
            }
            
            ++forcedResIt;
        }
        if (optionalResIt != optionalResidentsIdxs.end())
        { 
            int tries = chances;
            int currAddress = *optionalResIt;
            Resident* curr = _residents[*optionalResIt];
            std::set<int> possibleAddresses = _city->getAddressesWithin(
                resToOldAddrMap[curr],
                100
            );
            std::set<int> openHouses = getOnlyOpenHouses(possibleAddresses);
            openHouses.insert(currAddress);
            std::map<double, int> happinessToAddress = {};
            double highHappiness = -1;
            double currAddressHappiness = -1;
            for (int address : openHouses)
            {  
                if (tries == 0)
                    break;
                std::vector<int> adjacentAddresses =
                    _city->getAdjacentAdresses(address);
                std::vector<Color> adjacentColors;
                for (int address : adjacentAddresses)
                { 
                    if (_curr_addr_to_res_map.count(address) != 0)
                    {
                        adjacentColors.push_back(
                            (_curr_addr_to_res_map[address])->getColor()
                        );
                    }
                } 
                double happiness = curr->getHappiness(
                    adjacentColors,
                    adjacentAddresses.size()
                );
                if (address == currAddress)
                    currAddressHappiness = happiness;
                highHappiness = happiness > highHappiness ? happiness : highHappiness;
                happinessToAddress.insert(
                    std::pair<double, int>(happiness, address)
                );
                --tries;
            }
            if (highHappiness != currAddressHappiness)
            {
                _curr_addr_to_res_map.insert(std::pair<int, Resident*>(
                    happinessToAddress[highHappiness],
                    curr
                ));
            }

            ++optionalResIt;
            
        }
        counter--;
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

std::pair<std::vector<int>, std::vector<int>> Simulator::getMovingResidentIndices()
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

std::vector<Resident*> Simulator::getMovingResidents(
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

std::map<Resident*, int> Simulator::getOldAddresses (std::vector<Resident*> residents)
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