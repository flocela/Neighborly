#include "Simulator_Basic_B.h"

using namespace std;

Simulator_Basic_B::Simulator_Basic_B (
    const City* city,
    std::unordered_set<Resident*> residents,
    double percentOfResidents, // percent of residents that are chosen to move each run.
    int numOfHousesToChooseFrom, // number of houses the residents can choose from
    std::unique_ptr<CityState> cityState
    ): Simulator_Basic(
            city,
            residents,
            percentOfResidents,
            numOfHousesToChooseFrom,
            move(cityState))
    {}

string Simulator_Basic_B::toString() const
{
    return "Simulator Basic B";
}

bool Simulator_Basic_B::doMoveResident (
        double newHouseHappiness,
        const Resident* resident,
        const CityState* cityState,
        const City* city,
        int curAddress
) const
{
    (void)cityState;
    (void)city;
    (void)curAddress;
    return newHouseHappiness >= resident->getHappinessGoal();
}
