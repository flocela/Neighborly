#include "CityFactory_Grid.h"
#include "City_Grid.h"

using namespace std;

unique_ptr<City> CityFactory_Grid::createCity (
    UI& ui,
    int deltaX, 
    int deltaY
)
{
    int width = askForGridWidth(ui, min(deltaX, deltaY));
    return make_unique<City_Grid>(width);
}

string CityFactory_Grid::cityType () 
{
    return "Grid City";
}

int CityFactory_Grid::askForGridWidth(UI& ui, int maxWidth)
{   
    string _width_of_grid_orig_prompt_copy = _width_of_grid_orig_prompt;
    string _width_of_grid_range_prompt_copy = _width_of_grid_range_prompt;

    Question_Int question{
        0, //id
        1, // min number of houses
        maxWidth, // max number of houses
        _width_of_grid_orig_prompt_copy.insert(109, to_string(maxWidth)),
        _width_of_grid_type_prompt,
        _width_of_grid_range_prompt_copy.insert(99, to_string(maxWidth))
    };

    ui.getAnswer(question);
    if (question.hasValidAnswer()){
        return stoi(question.getAnswer());
    }
    else
    {
        string _width_of_grid_failure_copy = _width_of_grid_failure;
        ui.print(_width_of_grid_failure_copy.insert(53, to_string(maxWidth/2)));
        return maxWidth/2;
    }
        
}
