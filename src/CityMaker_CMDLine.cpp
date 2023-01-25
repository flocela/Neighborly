#include "CityMaker_CMDLine.h"
#include "UI_CMDLine.h"

using namespace std;

CityMaker_CMDLine::CityMaker_CMDLine (const UI_CMDLine& ui)
:_ui{ui}
{}

unique_ptr<City> CityMaker_CMDLine::makeCity (
    const std::vector<unique_ptr<CityFactory>>& cityFactories,
    int maxDeltaX,
    int maxDeltaY
)
{
    vector<string> namesOfCityFactories = {};
    for (auto& factory : cityFactories)
    {
        namesOfCityFactories.push_back(factory->cityType()); // TODO should factory be a reference?
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
            _ui.menu("Choose a city type by typing the corresponding number. _",
            namesOfCityFactories,
            _fall_back,
            _choosing_city_failure);  
    }
    return cityFactories[cityChoice]->createCity(_ui, maxDeltaX, maxDeltaY);

}
