#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Resident.h"
#include "City.h"
#include <vector>
#include <map>
#include <set>

class Simulator
{
    private:
        City* _city;
        std::set<int>::iterator selectRandom(const std::set<int> &s, size_t n);


    public:
        Simulator (City* city);
        Simulator () = delete;
        Simulator (const Simulator& o) = default;
        Simulator (Simulator&& o) noexcept = default;
        Simulator& operator= (const Simulator& o) = default;
        ~Simulator () = default;
        std::map<int, Resident*> startSimulation(std::vector<Resident*> residents);

};

#endif