#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <unordered_map>
#include "House.h"
#include "Resident.h"
#include "ResPerHouse.h"

// Peforms simulation runs.
class Simulator
{

protected:

    Simulator () = default;
    Simulator (const Simulator& o) = default;
    Simulator (Simulator&& o) noexcept = default;
    Simulator& operator= (const Simulator& o) = default;
    Simulator& operator= (Simulator&& o) noexcept = default;

public:

    virtual ~Simulator () noexcept = default;
    
    virtual ResPerHouse run() = 0;
    virtual std::string toString() const = 0;
};

#endif