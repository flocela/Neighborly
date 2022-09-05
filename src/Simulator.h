#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include "Resident.h"
#include "House.h"

class Simulator
{
    public:
        virtual std::unordered_map<const House*, Resident*> simulate() = 0;
};

#endif