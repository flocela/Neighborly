#ifndef CITYSTATE_H
#define CITYSTATE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "House.h"
#include "Resident.h"

using namespace std;

// Keeps track of the state of a city: where residents live and which houses are empty.
class CityState
{

protected:

    CityState () = default;
    CityState (const CityState& o) = default;
    CityState (CityState&& o) noexcept = default;
    CityState& operator= (const CityState& o) = default;
    CityState& operator= (CityState&& o) noexcept = default;

public:

    virtual ~CityState () noexcept = default;

    virtual void moveOut (Resident* resident) = 0;
    virtual void moveIn (Resident* resident, const House* house) = 0;
    virtual void moveOutAndIntoHouse (Resident* resident, const House* house) = 0;
    virtual std::vector<const House*> getOpenHousesWithinRange (
        double centerX,
        double centerY,
        double allowableDistance) const = 0;
    virtual std::unordered_set<const House*> getOpenHouses() const = 0;
    virtual std::unordered_map<const House*, Resident*> getResidentsPerHouse () const = 0;

    // Returns nullptr if resident does not have a house.
    virtual const House* getHousePerResident(Resident* resident) const = 0;

    // Returns nullptr if house is empty.
    virtual Resident* getResidentPerHouse(const House* house) const = 0;
};

#endif