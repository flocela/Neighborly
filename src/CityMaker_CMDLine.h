#ifndef CITYMAKER_CMDLINE_H
#define CITYMAKER_CMDLINE_H

#include "CityMaker.h"
#include "UI_CMDLine.h"

class CityMaker_CMDLine: public CityMaker
{
public:

    CityMaker_CMDLine (const UI& ui);
    CityMaker_CMDLine () = delete;
    CityMaker_CMDLine (const CityMaker_CMDLine& o) = default;
    CityMaker_CMDLine (CityMaker_CMDLine&& o) noexcept = default;
    CityMaker_CMDLine& operator= (const CityMaker_CMDLine& o) = default;
    CityMaker_CMDLine& operator=(CityMaker_CMDLine&& o) noexcept = default;
    ~CityMaker_CMDLine () = default;

    std::unique_ptr<City> makeCity (
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories,
        int maxDeltaX,
        int maxDeltaY
    )
    override;

private:
    const UI& _ui;
    int _fall_back = 0;
    std::string _choosing_city_failure = "Couuld not determine the city type, will be using .";
};

#endif