#include "CityFactory_Grid.h"

#include "City_Grid.h"

std::unique_ptr<City> CityFactory_Grid::createCity (UI& ui)
{
    int width = askForGridWidth(ui);
    return std::make_unique<City_Grid>(width);
}

std::string CityFactory_Grid::toString ()
{
    return "CityFactory_Grid";
}

int CityFactory_Grid::askForGridWidth(UI& ui)
{
    Question_Int question = createQuestionGridWidth();
    ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else
        throw _width_of_grid_failure;
}

Question_Int CityFactory_Grid::createQuestionGridWidth ()
{   std::string x = _width_of_grid_range_prompt;
    return Question_Int{0,
                        1,
                        100,
                        _width_of_grid_orig_prompt,
                        _width_of_grid_type_prompt,
                        _width_of_grid_range_prompt};
}

