#include "CityMaker_CMDLine.h"
#include "UI_CMDLine.h"

// TODO CityMaker_CMDLine.cpp not checked
std::unique_ptr<City> CityMaker_CMDLine::makeCity (
    std::vector<CityFactory*> cityFactories,
    int maxDeltaX,
    int maxDeltaY
)
{
    std::vector<std::string> namesOfCityFactories = {};
    for (auto& factory : cityFactories)
    {
        namesOfCityFactories.push_back(factory->nameOfCities());
    }

    int cityChoice = 0;

    if (cityFactories.size() == 1)
    {
        std::cout << "\nWell, there's only one type of city to choose. So your city type will be " <<
        cityFactories[0]->nameOfCities() << std::endl;
        return cityFactories[cityChoice]->createCity(_ui, maxDeltaX, maxDeltaY);
    }
    else
    {
        int cityChoice = 
            _ui.menu("Choose a city type by typing the"
            " corresponding number.",
            namesOfCityFactories
            );
        return cityFactories[cityChoice]->createCity(_ui, maxDeltaX, maxDeltaY);
    }
    
    
}