#ifndef CITYFACTORY_GRID_H
#define CITYFACTORY_GRID_H

#include "CityFactory.h"
#include "Question_Int.h"

// CityFactory_Grid creates a City_Grid.
class CityFactory_Grid: public CityFactory
{
public:
    CityFactory_Grid () = default;
    CityFactory_Grid (const CityFactory_Grid& obj) = default;
    CityFactory_Grid (CityFactory_Grid&& obj) noexcept = default;
    CityFactory_Grid& operator=(const CityFactory_Grid& obj) = default;
    CityFactory_Grid& operator=(CityFactory_Grid&& obj) noexcept = default;
    ~CityFactory_Grid () noexcept = default;

    std::string cityType () const override;

    std::unique_ptr<City> createCity (
        const UI& ui, 
        int max_width, 
        int max_height
    ) const override;
    

private:

    // ask user for grid width with these prompts
    std::string _width_of_grid_orig_prompt =
        "\nEnter the width of the grid, (how many houses per side)?"
        " The minimum width is 1 house. The maximum width is  houses.";
    std::string _width_of_grid_type_prompt = 
        "Nope, that's not a whole number. Should be a number without any"
        " decimals.";
    std::string _width_of_grid_range_prompt = 
        "That number is either too small or too large. Minimum allowed width"
        " is 1, maximum allowed width is .";
    std::string _width_of_grid_failure = 
        "Can not get a proper grid width. Using grid width of .";

    
    int askForGridWidth(const UI& ui, int maxWidth) const;
    
    // inserts additional string at location
    std::string insertIntoString (
    std::string str, 
    int location,
    std::string insert) const;
};

#endif