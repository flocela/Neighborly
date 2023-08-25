#ifndef CITYMAKER_CMDLINE__H
#define CITYMAKER_CMDLINE__H

#include "CityMaker.h"
#include "UI.h"

class CityMaker_CmdLine: public CityMaker
{

public:

    CityMaker_CmdLine (const UI& ui);
    CityMaker_CmdLine () = delete;
    CityMaker_CmdLine (const CityMaker_CmdLine& o) = default;
    CityMaker_CmdLine (CityMaker_CmdLine&& o) noexcept = default;
    CityMaker_CmdLine& operator= (const CityMaker_CmdLine& o) = default;
    CityMaker_CmdLine& operator=(CityMaker_CmdLine&& o) noexcept = default;
    ~CityMaker_CmdLine () noexcept = default;

    std::unique_ptr<City> makeCity (
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories,
        int maxDeltaX,
        int maxDeltaY
    )
    override;

private:

    const UI& _ui;

    // If the user can not choose a city from the menu, then choose the first city.
    int _fall_back = 0; 

    std::string _choosing_city_failure = "Could not determine the city type, will be using .";
};

#endif