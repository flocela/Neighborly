#include "CityMaker_CmdLine.h"
#include "UI_CmdLine.h"

using namespace std;

CityMaker_CmdLine::CityMaker_CmdLine (const UI& ui)
: _ui{ui}
{}

unique_ptr<City> CityMaker_CmdLine::makeCity (
    const std::vector<unique_ptr<const CityFactory>>& cityFactories,
    int maxDeltaX,
    int maxDeltaY
)
{
    // The current city choice is the made by the factory at index zero in @cityFactories.
    int cityChoice = 0;

    string prompt = "";

    // If there is only one city factory, then ask user to choose that one.
    if (cityFactories.size() == 1)
    {
        prompt = "\nChoose a city type by typing the corresponding number."
        " There's only one city type to choose from, please enter 1.";
    }
    else
    {
        prompt = "\nChoose a city type by typing the corresponding number.";
    }

    // Create vector of city type names to display to the user.
    vector<string> namesOfCityFactories = {};
    for (auto& factory : cityFactories)
    {
        namesOfCityFactories.push_back(factory->cityType());
    }

    // Use a menu to ask user to choose city.

    // Create response string in the case that user can not give a proper response to the menu.
    string failureResponseWithBackupCity = _choosing_city_failure;
    failureResponseWithBackupCity.insert(49, namesOfCityFactories[_fall_back]);

    cityChoice = _ui.menu(prompt,
                            namesOfCityFactories,
                            _fall_back,
                            failureResponseWithBackupCity);

    // Create city based on cityChoice.
    return cityFactories[cityChoice]->createCity(_ui, maxDeltaX, maxDeltaY);

}