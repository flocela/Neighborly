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

#include "ResidentsFactory_Flat.h"
#include "ResidentsFactory_StepDown.h"
#include "ResidentsFactory.h"

#include "Printer_Graphic.h"
#include "Printer_CMDLine.h"
#include "Resident_Flat.h"
#include "Simulator.h"
#include "Simulator_Basic_A.h"
#include "Color.h"
#include "City_Grid.h"
#include "Resident_StepDown.h"
#include "Resident_Flat.h"
#include "MainBaseQuestion.h"
#include "SimulationComponents.h"
#include "MainExamples.h"
#include "UserComponentsGetter.h"
#include <chrono>
#include <ctime>

using namespace std;

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

/* Function Declarations */
template<typename T>
set<T*> getSetOfPointers (vector<unique_ptr<T>>& ts)
{
    set<T*> pointers = {};
    for (auto& t : ts)
    {
        pointers.insert(t.get());
    }
    return pointers;
}

vector<unique_ptr<CityFactory>> initCityFactories ();
vector<unique_ptr<ResidentsFactory>> initResidentFactories ();
void initForSimpleExample (int example);
void initForUserDefinedRun ();

const int SCREEN_WIDTH   = 2400;
const int SCREEN_HEIGHT  = 1200;
const int MAX_HOUSES_X   = 120;
const int MAX_HOUSES_Y   = 120;

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    vector<unique_ptr<CityFactory>> cityFactories = initCityFactories();
    vector<unique_ptr<ResidentsFactory>> residentFactories = initResidentFactories();

    SimulationComponents components;

    UI_CMDLine cmdLine{};

    MainBaseQuestion mainQuestion;
    bool usesExamples = mainQuestion.askUserToUsePremadeExamples(cmdLine);
    if (usesExamples)
    {   
        MainExamples mainExamples; //TODO add randomSeed number to MainExamples

        components = mainExamples.userChoosesExample(cmdLine);
    }
    else
    {
       UserComponentsGetter userComponentsGetter{};
       components = userComponentsGetter.askUserForComponents(
           cmdLine,
           cityFactories,
           residentFactories,
           MAX_HOUSES_X,
           MAX_HOUSES_Y
       );
    }
    
    srand(components.randomSeed);
    vector<const House*> houses = components.city->getHouses();

    unordered_map<const House*, set<const House*>> neighboringHousesPerHouse;
    for (const House* house : houses)
    {   
        neighboringHousesPerHouse[house] = components.city->getAdjacentHouses(house->getAddress());
    }

    unique_ptr<Renderer> renderer = make_unique<Renderer>(
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        "Neighbors");

    Printer_Graphic graphicPrinter{
        move(renderer),
        components.baseColorsPerGroupid,
        components.city->getCoordinatesPerHouse(),
        neighboringHousesPerHouse,
        "Neighbors",
        components.numOfRuns
    };
    
    unordered_map<const House*, Resident*> residentPerHouse;
    for (int ii=0; ii<components.numOfRuns; ii++)
    {   
        residentPerHouse = components.simulator->simulate();

        // Printer_Graphic requires unordered_map of type CONST House* and CONST Resident*
        unordered_map<const House*, const Resident*> constResPerConstHouse;
        for (auto& pair : residentPerHouse)
        {
            constResPerConstHouse[pair.first] = pair.second;
        }

        graphicPrinter.print(constResPerConstHouse, ii);

    }
    //Printer_CMDLine cmdLinePrinter{components.numOfRuns, components.city.get()};
    //cmdLinePrinter.print(houseToResidentMap, numOfRuns, "Title");
    graphicPrinter.keepScreen();
    return 0; 
}

vector<unique_ptr<CityFactory>> initCityFactories ()
{
    vector<unique_ptr<CityFactory>> cityFactories{};
    cityFactories.emplace_back(make_unique<CityFactory_Grid>());
    return cityFactories;
}

vector<unique_ptr<ResidentsFactory>> initResidentFactories()
{
    vector<unique_ptr<ResidentsFactory>> residentFactories = {};
    residentFactories.emplace_back(make_unique<ResidentsFactory_Flat>());
    residentFactories.emplace_back(make_unique<ResidentsFactory_StepDown>());
    //TODO add the rest of the fatories here. Once they're made.
    return residentFactories;
}
