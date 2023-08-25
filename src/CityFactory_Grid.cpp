#include "City_Grid.h"
#include "CityFactory_Grid.h"
#include "Question_Int.h"

using namespace std;

string CityFactory_Grid::cityType () const
{
    return "Grid City";
}

unique_ptr<City> CityFactory_Grid::createCity (const UI& ui, int maxWidth, int maxHeight) const
{
    int width = askForGridWidth(ui, min(maxWidth, maxHeight));

    return make_unique<City_Grid>(width);
}

int CityFactory_Grid::askForGridWidth(const UI& ui, int maxWidth)const
{   
    Question_Int question{
        0,          //id
        1,          // min number of houses on a side
        maxWidth,   // max number of houses on a side
        true,       // min is inclusive
        true,       // max is inclusive
        maxWidth/2, // fallback number of houses
        insertIntoString( // add max width of grid to original prompt
            _grid_width_orig_prompt,
            _grid_width_orig_prompt.size()-8,
            to_string(maxWidth)),
        "city grid width" // name of value
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
