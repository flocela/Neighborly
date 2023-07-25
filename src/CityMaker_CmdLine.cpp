#include "CityMaker_CmdLine.h"
#include "UI_CmdLine.h"

using namespace std;

CityMaker_CmdLine::CityMaker_CmdLine (const UI& ui)
:_ui{ui}
{}

unique_ptr<City> CityMaker_CmdLine::makeCity (
    const std::vector<unique_ptr<const CityFactory>>& cityFactories,
    int maxDeltaX,
    int maxDeltaY
)
{
    vector<string> namesOfCityFactories = {};
    for (auto& factory : cityFactories)
    {
        namesOfCityFactories.push_back(factory->cityType());
    }

    int cityChoice = 0;

    string copyChoosingCityFailure = _choosing_city_failure;
    copyChoosingCityFailure.insert(49, namesOfCityFactories[_fall_back]);

    if (cityFactories.size() == 1)
    {
        cout << "\nWell, there's only one type of city, so your city type will be " <<
        cityFactories[0]->cityType() << ". " << endl;
    }
    else
    {
        cityChoice = 
            _ui.menu("Choose a city type by typing the corresponding number.",
            namesOfCityFactories,
            _fall_back,
            _choosing_city_failure);  
    }
    return cityFactories[cityChoice]->createCity(_ui, maxDeltaX, maxDeltaY);

}