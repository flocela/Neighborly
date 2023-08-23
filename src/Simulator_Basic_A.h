#ifndef SIMULATOR_BASIC_A__H
#define SIMULATOR_BASIC_A__H

#include "Simulator_Basic.h"

// The steps in a run can be found in the parent class, which is Simulator_Basic.
// Deciding whether a resident is ultimately moved in a run is determined in
// doMoveResident().
class Simulator_Basic_A: public Simulator_Basic
{

public:

    Simulator_Basic_A (
        const City* city,
        std::unordered_set<Resident*> residents,
        double percentOfResidents, // percent of residents that are chosen to move each run.
        int numOfHousesToChooseFrom, // number of houses the residents can choose from
        std::unique_ptr<CityState> cityState
    );
    Simulator_Basic_A () = delete;
    ~Simulator_Basic_A () noexcept = default;

    std::string toString() const override;

protected:

    Simulator_Basic_A (const Simulator_Basic_A& o) = default;
    Simulator_Basic_A (Simulator_Basic_A&& o) noexcept = default;
    Simulator_Basic_A& operator= (const Simulator_Basic_A& o) = default;
    Simulator_Basic_A& operator= (Simulator_Basic_A&& o) noexcept = default;

    // If @newHouseHappiness is greater or equal to the resident's current happiness, then
    // returns true. Otherwise returns false.
    bool doMoveResident (
        double newHouseHappiness,
        const Resident* resident,
        const CityState* cityState,
        const City* city,
        int curAddress) const override;
};

#endif