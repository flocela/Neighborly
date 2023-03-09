#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <unordered_map>
#include "Resident.h"
#include "House.h"

class Simulator
{
protected:
    Simulator () = default;
    Simulator (const Simulator& o) = default;
    Simulator (Simulator&& o) noexcept = default;
    Simulator& operator= (const Simulator& o) = default;
    Simulator& operator= (Simulator&& o) noexcept = default;

public:
    virtual ~Simulator () = default;
    virtual std::unordered_map<const House*, Resident*> run() = 0;
    virtual std::string toString() = 0;
};

#endif