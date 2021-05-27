#ifndef CITYMAKER_CMDLINE_H
#define CITYMAKER_CMDLINE_H

#include "CityMaker.h"
#include "UI_CMDLine.h"

class CityMaker_CMDLine: public CityMaker
{
    public:
        std::unique_ptr<City> makeCity (
            std::vector<CityFactory*> cityFactories
        ) override;

    private:
        UI_CMDLine _ui = UI_CMDLine{};  
        std::vector<std::string> getFactoryNames (
            std::vector<CityFactory*> cityFactories
        ) const;
};

#endif