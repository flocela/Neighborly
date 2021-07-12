/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <memory>

#include "CityFactory.h"
#include "CityFactory_Grid.h"
#include "CityMaker_CMDLine.h"
#include "ResidentsFactory_Flat.h"
#include "ResidentsFactory.h"
#include "ResidentsMaker_CMDLine.h"
#include "Printer_Graphic.h"
#include "Resident_Flat.h"
#include "Simulator.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

std::vector<std::unique_ptr<CityFactory>> initCityFactories ();

std::vector<std::unique_ptr<ResidentsFactory>> initResidentFactories();

std::vector<CityFactory*> fromCityFactoriesGetPointers (
    std::vector<std::unique_ptr<CityFactory>>& cityFactories);

std::vector<ResidentsFactory*> fromResidentFactoriesGetPointers (
    std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories);

// I've set the SCREEN_WIDTH and SCREEN_HEIGHT to be 1200pixels. The city graph
// will take up 1/2 the screen. I want each house to take up no less than 4 pixels.
// Otherwise, the house will be difficult to see.  So the largest number 
// of houses I can have in the x and y directions are MAX_DELTA_X and MAX_DELTA_Y,
// calculated as 1200/2/4 = 150. Each house takes up at least 4 pixels, there
// are 150 houses, that makes 600 pixels or half the screen width.
const int SCREEN_WIDTH  = 1200;
const int SCREEN_HEIGHT = 1200;
const int MAX_DELTA_X   = 150;
const int MAX_DELTA_Y   = 150;

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    std::vector<std::unique_ptr<CityFactory>> cityFactories =
        initCityFactories();
    std::vector<std::unique_ptr<ResidentsFactory>> residentFactories =
        initResidentFactories();
    std::vector<CityFactory*> cityFactoryPointers =
        fromCityFactoriesGetPointers(cityFactories);
    std::vector<ResidentsFactory*> residentFactoryPointers =
        fromResidentFactoriesGetPointers(residentFactories);; 

    CityMaker_CMDLine cityMaker{};
    /*std::unique_ptr<City> city = cityMaker.makeCity(
        cityFactoryPointers,
        MAX_DELTA_X,
        MAX_DELTA_Y);*/
    std::unique_ptr<City> city = cityMaker.makeBaseCity(
        cityFactoryPointers, 
        MAX_DELTA_X, 
        MAX_DELTA_Y
    );

    ResidentsMaker_CMDLine residentsMaker{};
    //std::vector<std::unique_ptr<Resident>> residents = 
    //    residentsMaker.makeResidents(residentFactoryPointers, city->getSize(), _the_color_Infos);
    std::vector<std::unique_ptr<Resident>> residents = 
        residentsMaker.makeBaseResidents(residentFactoryPointers, city->getSize(), _the_color_Infos);
    
    std::vector<Resident*> residentPtrs = {};
    for (auto& resident: residents)
    {
        residentPtrs.push_back(resident.get());
    }
    
/*
    std::map<int, Resident*> houseToResidentMap = {};
    for (auto& resident : residents)
    {
        houseToResidentMap[resident->getID()] = resident.get();
    }*/
    Simulator simulator{city.get(), residentPtrs};
    Printer_Graphic printer{1200, 1200, city.get(), _the_color_Infos};
    for (int ii=0; ii< 3; ii++)
    {   
        std::map<House*, Resident*> houseToResidentMap = simulator.simulate();
        printer.print(houseToResidentMap, 1, 1, "Title");
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        
    }
    printer.keepScreen();
    return 0; 
}

std::vector<std::unique_ptr<CityFactory>> initCityFactories ()
{
    std::vector<std::unique_ptr<CityFactory>> cityFactories = {};
    cityFactories.emplace_back(std::make_unique<CityFactory_Grid>());
    return cityFactories;
}

std::vector<std::unique_ptr<ResidentsFactory>> initResidentFactories()
{
    std::vector<std::unique_ptr<ResidentsFactory>> residentFactories = {};
    residentFactories.emplace_back(std::make_unique<ResidentsFactory_Flat>());
    return residentFactories;
}

std::vector<CityFactory*> fromCityFactoriesGetPointers (
    std::vector<std::unique_ptr<CityFactory>>& cityFactories)
{
    std::vector<CityFactory*> cityFactoryPointers = {};
    for (auto& factory: cityFactories)
    {
        cityFactoryPointers.push_back(factory.get());
    }
    return cityFactoryPointers;
}

std::vector<ResidentsFactory*> fromResidentFactoriesGetPointers (
    std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories)
{
    std::vector<ResidentsFactory*> residentFactoryPointers = {};
    for (auto& factory : residentFactories)
    {
        residentFactoryPointers.push_back(factory.get());
    }
    return residentFactoryPointers;
}
