#ifndef SIMULATOR_BASIC_B_H
#define SIMULATOR_BASIC_B_H

#include "Simulator_Basic.h"

// Performs the simulation runs.
// The steps in a run can be found in Simulator_Basic.
// Deciding whether a resident is ultimately moved in a run is determined in
// doMoveResident().
class Simulator_Basic_B: public Simulator_Basic
{
public:
    Simulator_Basic_B (
        const City* city,
        std::unordered_set<Resident*> residents,
        double percentOfResidents, // percent of residents that are chosen to move each run.
        int numOfHousesToChooseFrom, // number of houses the residents can choose from
        std::unique_ptr<CityState> cityState
    );
    Simulator_Basic_B () = delete;
    ~Simulator_Basic_B () noexcept = default;

    std::string toString() const override;

protected:
    Simulator_Basic_B (const Simulator_Basic_B& o) = default;
    Simulator_Basic_B (Simulator_Basic_B&& o) noexcept = default;
    Simulator_Basic_B& operator= (const Simulator_Basic_B& o) = default;
    Simulator_Basic_B& operator= (Simulator_Basic_B&& o) noexcept = default;

    // If the newHouseHappiness is greater or equal to the resident's happiness goal, then returns true.
    // Otherwise returns false.
    bool doMoveResident (
        double newHouseHappiness,
        const Resident* resident,
        const CityState* cityState,
        const City* city,
        int curAddress) const override;

};

#endif