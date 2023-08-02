#ifndef CITYMAKER_H
#define CITYMAKER_H

#include <memory>
#include <vector>
#include "City.h"
#include "CityFactory.h"

class CityMaker
{

protected:

    CityMaker () = default;
    CityMaker (const CityMaker& o) = default;
    CityMaker (CityMaker&& o) noexcept = default;
    CityMaker& operator= (const CityMaker& o) = default;
    CityMaker& operator= (CityMaker&& o) noexcept = default;

public:

    virtual ~CityMaker () noexcept = default;
    
    virtual std::unique_ptr<City> makeCity (
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories,
        int maxDeltaX,
        int maxDeltaY
    ) = 0;
        
};

#endif