#include "CityFactory_Grid.h"

#include "City_Grid.h"

std::unique_ptr<City> CityFactory_Grid::createCity (
    UI& ui,
    int deltaX, 
    int deltaY
)
{
    
    int width = askForGridWidth(ui, std::min(deltaX, deltaY));
    return std::make_unique<City_Grid>(width);
}

std::string CityFactory_Grid::toString ()
{
    return "CityFactory_Grid";
}

std::string CityFactory_Grid::nameOfCities () 
{
    return "Grid City";
}

int CityFactory_Grid::askForGridWidth(UI& ui, int maxWidth)
{
    Question_Int question{
        0,
        1,
        maxWidth,
        _width_of_grid_orig_prompt.insert(109, std::to_string(maxWidth)),
        _width_of_grid_type_prompt,
        _width_of_grid_range_prompt.insert(99, std::to_string(maxWidth))
    };

    ui.getAnswer(question);
    if (question.hasValidAnswer()){
        return std::stoi(question.getAnswer());
    }
        
    else
        throw _width_of_grid_failure;
}
