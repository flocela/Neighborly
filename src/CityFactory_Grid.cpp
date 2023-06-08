#include "CityFactory_Grid.h"
#include "City_Grid.h"
#include "Question_Int.h"

using namespace std;


string CityFactory_Grid::cityType () const
{
    return "Grid City";
}

unique_ptr<City> CityFactory_Grid::createCity (
    const UI& ui,
    int deltaX, 
    int deltaY
) const
{
    int width = askForGridWidth(ui, min(deltaX, deltaY));
    return make_unique<City_Grid>(width);
}

int CityFactory_Grid::askForGridWidth(const UI& ui, int maxWidth)const
{   
    string copyWidthOfGridOrig = _width_of_grid_orig_prompt;
    string copyWidthOfGridRange = _width_of_grid_range_prompt;
    string copyWidthOfGridFailure = _width_of_grid_failure;
    copyWidthOfGridFailure.insert(53, to_string(maxWidth/2));

    Question_Int question{
        0, //id
        1, // min number of houses on a side
        maxWidth, // max number of houses on a side
        true, // min is inclusive
        true, // max is inclusive
        maxWidth/2, // fallback number of houses
        insertIntoString(_width_of_grid_orig_prompt, 109, to_string(maxWidth)),
        "city grid width"
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

std::string CityFactory_Grid::insertIntoString  (
    string str,
    int location,
    string insert
) const
{
    string modifiedString = str;
    return modifiedString.insert(location, insert);
}
