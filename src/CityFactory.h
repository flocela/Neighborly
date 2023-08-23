#ifndef CITYFACTORY__H
#define CITYFACTORY__H

#include <memory>
#include "City.h"
#include "UI.h"

class CityFactory
{

protected:

    CityFactory () = default;
    CityFactory (const CityFactory& o) = default;
    CityFactory (CityFactory&& o) noexcept = default;
    CityFactory& operator= (const CityFactory& o) = default;
    CityFactory& operator= (CityFactory&& o) noexcept = default;

public:

    virtual ~CityFactory () noexcept = default;
    
    // Returns the name of the type of city that is produced.
    virtual std::string cityType () const = 0; 
    
    virtual std::unique_ptr<City> createCity (
        const UI& ui, 
        int max_width, 
        int max_height
    ) const = 0;
};

#endif