#ifndef CITYFACTORY_GRID__H
#define CITYFACTORY_GRID__H

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
        int maxWidth, 
        int maxHeight
    ) const override;
    
private:

    // Ask user for grid width using this prompt.
    std::string _grid_width_orig_prompt =
        "\nEnter the width of the grid, (how many houses per side)?"
        " The minimum width is 1 house. The maximum width is  houses.";

    int askForGridWidth(const UI& ui, int maxWidth) const;
    
    // Inserts additional character position in sting.
    std::string insertIntoString (
    std::string str, 
    int location,
    std::string insert) const;
};

#endif