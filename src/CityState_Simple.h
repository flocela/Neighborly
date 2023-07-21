#ifndef CITYSTATE_SIMPLE_H
#define CITYSTATE_SIMPLE_H

#include "CityState.h"

#include <vector>
#include <unordered_map>

#include "City.h"
#include "House.h"

class CityState_Simple : public CityState
{
public:
    CityState_Simple (
        const City* city
    );
    CityState_Simple () = delete;
    CityState_Simple (const CityState_Simple& o) = default;
    CityState_Simple (CityState_Simple&& o) noexcept = default;
    CityState_Simple& operator= (const CityState_Simple& o) = default;
    CityState_Simple& operator= (CityState_Simple&& o) noexcept = default;
    ~CityState_Simple () noexcept = default;

    void moveOut (Resident* resident) override;
    void moveIn (Resident* resident, const House* house) override;
    void moveInAndOutOfHouse (Resident* resident, const House* house) override;

    std::vector<const House*> getOpenHousesWithinRange (
        double centerX,
        double centerY,
        double allowableDistance) const override;

    std::unordered_set<const House*> getOpenHouses() const;

    std::unordered_map<const House*, Resident*> getResidentsPerHouse () const override;
    const House* getHousePerResident(Resident* resident) const override;
    Resident* getResidentPerHouse(const House* house) const override;

private:
    const City* _city;
    std::vector<std::vector<std::unordered_set<const House*>>> _open_houses_per_y_x{};
    std::unordered_map<const House*, Resident*> _resident_per_house = {};
    std::unordered_map<Resident*, const House*> _house_per_resident{};


    double getDist (
        const double firstX,
        const double firstY,
        const double secondX,
        const double secondY
    ) const;

};

#endif