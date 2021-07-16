#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <map>
#include "Resident.h"
#include "House.h"

class Simulator
{
    public:
        virtual std::map<House*, Resident*> simulate() = 0;
};

#endif