#include "Simulator.h"
#include <algorithm>

Simulator::Simulator (City* city): _city{city} {}

std::map<int, Resident*> Simulator::startSimulation(std::vector<Resident*> residents)
{
    std::map<int, Resident*> addressToResidentMap = {};
    std::vector<int> addresses = _city->getAddresses();
    std::set<int> openAddresses;
    for (int address : addresses)
    {
        openAddresses.insert(address);
    }
    
    for (Resident* res : residents)
    {
        int size = openAddresses.size();
        int r = rand() % size;
        int address = *selectRandom(openAddresses, r);
        addressToResidentMap.insert({address, res});
        openAddresses.erase(address);
    }
    return addressToResidentMap;
}

std::set<int>::iterator Simulator::selectRandom(const std::set<int> &s, size_t n)
{
    std::set<int>::iterator it = std::begin(s);
    std::advance(it, n);
    return it;
}