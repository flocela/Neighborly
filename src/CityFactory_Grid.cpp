#include "CityFactory_Grid.h"
#include "City_Grid.h"

using namespace std;

unique_ptr<City> CityFactory_Grid::createCity (
    const UI& ui,
    int deltaX, 
    int deltaY
) const
{
    int width = askForGridWidth(ui, min(deltaX, deltaY));
    return make_unique<City_Grid>(width);
}

string CityFactory_Grid::cityType () 
{
    return "Grid City";
}

int CityFactory_Grid::askForGridWidth(const UI& ui, int maxWidth)const
{   
    string copyWidthOfGridOrig = _width_of_grid_orig_prompt;
    string copyWidthOfGridRange = _width_of_grid_range_prompt;
    string copyWidthOfGridFailure = _width_of_grid_failure;
    copyWidthOfGridFailure.insert(53, to_string(maxWidth/2));

    Question_Int question{
        0, //id
        1, // min number of houses
        maxWidth, // max number of houses
        copyWidthOfGridOrig.insert(109, to_string(maxWidth)),
        _width_of_grid_type_prompt,
        copyWidthOfGridRange.insert(99, to_string(maxWidth)),
        to_string(maxWidth/2),
        copyWidthOfGridFailure
    };

    ui.getAnswer(question);
    if (question.hasValidAnswer()){
        return stoi(question.getAnswer());
    }
    else
    {
        return maxWidth/2;
    }
        
}
