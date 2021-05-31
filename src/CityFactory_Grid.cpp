#include "CityFactory_Grid.h"

#include "City_Grid.h"

std::unique_ptr<City> CityFactory_Grid::createCity (
    UI& ui,
    int deltaX, 
    int deltaY
)
{
    (void) deltaX;
    (void) deltaY;
    int width = askForGridWidth(ui, deltaX);
    return std::make_unique<City_Grid>(width);
}

std::unique_ptr<City> CityFactory_Grid::createBaseCity (
    UI& ui,
    int deltaX, 
    int deltaY
)
{
    (void) deltaX;
    (void) deltaY;
    (void) ui;
    int width = 150;
    return std::make_unique<City_Grid>(width);
}

std::string CityFactory_Grid::toString ()
{
    return "CityFactory_Grid";
}

int CityFactory_Grid::askForGridWidth(UI& ui, int maxWidth)
{
    Question_Int question = createQuestionGridWidth(maxWidth);
    ui.getAnswer(question);
    if (question.hasValidAnswer())
        return std::stoi(question.getAnswer());
    else
        throw _width_of_grid_failure;
}

Question_Int CityFactory_Grid::createQuestionGridWidth (int maxWidth)
{   
    return Question_Int{0,
                        1,
                        maxWidth,
                        _width_of_grid_orig_prompt.insert(126, std::to_string(maxWidth)),
                        _width_of_grid_type_prompt,
                        _width_of_grid_range_prompt.insert(99, std::to_string(maxWidth))};
}

