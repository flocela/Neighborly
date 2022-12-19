#include "CityMaker_CMDLine.h"
#include "UI_CMDLine.h"

using namespace std;

// TODO CityMaker_CMDLine.cpp not checked
unique_ptr<City> CityMaker_CMDLine::makeCity (
    vector<CityFactory*> cityFactories,
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

    if (cityFactories.size() == 1)
    {
        cout << "\nWell, there's only one type of city, so your city type will be " <<
        cityFactories[0]->cityType() << ". " << endl;
    }
    else
    {
        cityChoice = 
            _ui.menu("Choose a city type by typing the"
            " corresponding number. _",
            namesOfCityFactories
            );   
    }
    return cityFactories[cityChoice]->createCity(_ui, maxDeltaX, maxDeltaY);

}
