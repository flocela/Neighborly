#ifndef CITYSTATE_H
#define CITYSTATE_H

#include <unordered_map>
#include <unordered_set>
#include "House.h"
#include "Resident.h"

using namespace std;
// keeps information on the state of the city and residents
class CityState
{
protected:
    CityState () = default;
    CityState (const CityState& o) = default;
    CityState (CityState&& o) noexcept = default;
    CityState& operator= (const CityState& o) = default;
    CityState& operator= (CityState&& o) noexcept = default;

public:
    virtual ~CityState () = default;
    virtual void moveOut (Resident* resident) = 0;
    virtual void moveIn (Resident* resident, const House* house) = 0;
    virtual void moveInAndOutOfHouse (Resident* resident, const House* house) = 0;
    virtual std::unordered_set<const House*> getOpenHousesWithinRange (
        double minX,
        double maxX,
        double minY,
        double maxY)const = 0;
    virtual std::unordered_map<const House*, Resident*> getResidentsPerHouse () const = 0;

    // returns nullptr if resident does not have a house
    virtual const House* getHousePerResident(Resident* resident) const = 0;

    // returns nullptr if house is empty
    virtual Resident* getResidentPerHouse(const House* house) const = 0;
};

#endif