#ifndef CITYFACTORY_GRID_H
#define CITYFACTORY_GRID_H

#include "CityFactory.h"
#include "Question_Int.h"

class CityFactory_Grid: public CityFactory
{
    public:
        CityFactory_Grid () = default;
        CityFactory_Grid (const CityFactory_Grid& obj) = default;
        CityFactory_Grid (CityFactory_Grid&& obj) noexcept = default;
        CityFactory_Grid& operator=(const CityFactory_Grid& obj) = default;
        CityFactory_Grid& operator=(CityFactory_Grid&& obj) noexcept = default;
        ~CityFactory_Grid() = default;

        std::unique_ptr<City>  createCity (UI& ui) override;
        std::string toString () override;
    private:
        int askForGridWidth(UI& ui);
        Question_Int createQuestionGridWidth ();

        // Width of grid prompts for question
        std::string _width_of_grid_orig_prompt =
            "Enter the width of the grid, as in how many houses wide each side"
            " will be. The minimum width is 1 house. The maximum width is 100 houses.  ";
        std::string _width_of_grid_type_prompt = 
            "Nope, that's not a whole number. Should be a number without any"
            " decimals.  ";
        std::string _width_of_grid_range_prompt = 
            "That number is either too small or too large. Minimum allowed width"
            " is 1, maximum allowed width is 100.  ";
        std::string _width_of_grid_failure = 
            "Can not get information needed to make a city from the user.";
};

#endif