#ifndef CITYFACTORY_H
#define CITYFACTORY_H

#include "City.h"
#include "UI.h"
#include <map>
#include <string>
#include <memory>

// TODO CityFactory is not checked
class CityFactory
{
protected:
    CityFactory () = default;
    CityFactory (const CityFactory& o) = default;
    CityFactory (CityFactory&& o) noexcept = default;
    CityFactory& operator= (const CityFactory& o) = default;
    CityFactory& operator= (CityFactory&& o) noexcept = default;

public:
    virtual ~CityFactory () = default;
    
    // returns the name of the type of cities that are produced.
    virtual std::string cityType () const = 0; 
    
    virtual std::unique_ptr<City> createCity (
        const UI& ui, 
        int max_width, 
        int max_height
    ) const = 0;
};

#endif