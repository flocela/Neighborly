#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Resident.h"
#include "City.h"
#include <vector>
#include <map>
#include <set>
#include <utility>

class Simulator
{
    private:
        City* _city;
        std::vector<Resident*> _residents;
        std::map<int, Resident*> _curr_addr_to_res_map = {};

        std::set<int>::iterator selectRandom (const std::set<int> &s, size_t n);
        void firstSimulation ();
        std::set<int> getSetOfAddresses ();
        std::set<int> getSetOfInts (int max);
        std::pair<std::vector<int>, std::vector<int>> getMovingResidentIndices ();
        std::vector<Resident*> getMovingResidents (std::vector<int> residentIndices);
        std::map<Resident*, int> getOldAddresses(std::vector<Resident*> residents);
        void openHouses (std::vector<Resident*> residents);
        std::set<int> getOnlyOpenHouses (std::set<int> addresses);

    public:
        Simulator (City* city, std::vector<Resident*> residents);
        Simulator () = delete;
        Simulator (const Simulator& o) = default;
        Simulator (Simulator&& o) noexcept = default;
        Simulator& operator= (const Simulator& o) = default;
        ~Simulator () = default;
        std::map<int, Resident*> simulate();

};

#endif