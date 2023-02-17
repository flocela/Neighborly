#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <unordered_map>
#include "Resident.h"
#include "House.h"

class Simulator
{
    public:
        virtual std::unordered_map<const House*, Resident*> simulate() = 0;
        virtual std::string toString() = 0;
};

#endif