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

#include <chrono>
#include <iostream>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <thread>

#include "CityFactory.h"
#include "CityFactory_Grid.h"
#include "City_Grid.h"
#include "Color.h"
#include "FromExamplesStarter.h"
#include "FromQuestionsStarter.h"
#include "FromFileStarter.h"
#include "Printer_Graphic.h"
#include "Printer_CMDLine.h"
#include "Renderer_SDL.h"
#include "ResidentsFactory_Falling.h"
#include "ResidentsFactory_Flat.h"
#include "ResidentsFactory_Rising.h"
#include "ResidentsFactory_StepDown.h"
#include "ResidentsFactory_StepUp.h"
#include "ResidentsFactory.h"
#include "Simulator.h"
#include "Simulator_Basic_A.h"
#include "SimulationComponents.h"
#include "UsePremadeExampleQuestion.h"

using namespace std;

#define FONT_PATH "assets/pacifico/Pacifico.ttf"

const vector<unique_ptr<const CityFactory>> initCityFactories ();
const vector<unique_ptr<const ResidentsFactory>> initResidentFactories ();

const int SCREEN_WIDTH = 2400;
const int SCREEN_HEIGHT = 1200;
const int MAX_HOUSES_X = 120;
const int MAX_HOUSES_Y = 120;
const int MAX_NUM_OF_RESIDENT_GROUPS = 2;
const int MAX_NUM_OF_RUNS = 200;

int main(int argc, char* argv[])
{   
    // Components will be populated by file, by premade examples, or by user cmd line choices.
    SimulationComponents components;
    bool usingFile = (argc >= 2);
    
    if (usingFile)
    {
        string inputFile = argv[1];
        FromFileStarter fromFileStarter{};
        components = fromFileStarter.createSimulationComponents("../" + inputFile);
    }
    else
    {   
        // Gather information from user using the cmd line
        const UI_CMDLine cmdLine{};

        // User chooses to use pre-made examples, or type in required information.
        UsePremadeExampleQuestion usePremadeExamplesQuestion;
        bool usingExamples = usePremadeExamplesQuestion.askUser(cmdLine);

        if (usingExamples)
        {   
            FromExamplesStarter fromExamplesStarter;
            components = fromExamplesStarter.userChoosesExample(cmdLine);
        }
        else
        {
            FromQuestionsStarter fromQuestionsStarter{};
            components = fromQuestionsStarter.askUserForComponents(
                cmdLine,
                initCityFactories(),
                initResidentFactories(),
                MAX_HOUSES_X,
                MAX_HOUSES_Y,
                MAX_NUM_OF_RUNS
            );
        }
    }

    // Throw exception if common input errors are made.
    if (components.city->getNumOfHouses() < (int)components.residents.size())
    {
        throw invalid_argument("Number of houses needs to be larger than number of residents.");
    }

    // Construct graphic printer
    Printer_Graphic graphicPrinter{
        make_unique<Renderer_SDL>(SCREEN_WIDTH, SCREEN_HEIGHT,"Neighbors"),
        components.baseColorsPerGroupid,
        components.city->getCoordinatesPerHouse(),
        *(components.city->getAdjacentHousesPerHouse()),
        "Neighbors",
        components.numOfRuns
    };

    // cmd line printer needs a CityPrinter
    unique_ptr<CityPrinter> cityPrinter = make_unique<CityPrinter>(components.city.get());

    // construct cmd line printer
    Printer_CMDLine cmdLinePrinter{
        *(cityPrinter.get()),
        components.baseColorsPerGroupid,
        components.numOfRuns,
    };

    // Start simulation. Simulation runs in a for-loop numOfRun times.
    // Run metrics are updated after each run. Results are printed after each run.

    // set seed for randomization for simulation.
    srand(components.randomSeed);

    RunMetrics runMetrics{
        *(components.city->getAdjacentHousesPerHouse()),
        components.randomSeed,
        components.simulator->toString()};

    for (int ii=0; ii<components.numOfRuns; ii++)
    {  
        unordered_map<const House*, const Resident*> residentsPerHouse = 
            components.simulator->run();
        runMetrics.updateMetrics(ii, residentsPerHouse);

        // every run should show for at least 1/4 second
        auto timeStart = std::chrono::high_resolution_clock::now();
        
        graphicPrinter.print(&runMetrics);
        
        cmdLinePrinter.print(&runMetrics);

        // show run for at least 1/4 second.
        std::this_thread::sleep_until(timeStart + std::chrono::milliseconds(250));
    }

    if (components.numOfRuns == 0)
    {
        graphicPrinter.print(&runMetrics);
        cmdLinePrinter.print(&runMetrics);
    }

    graphicPrinter.lastPrint();
    cmdLinePrinter.lastPrint();

    return 0; 
}

const vector<unique_ptr<const CityFactory>> initCityFactories ()
{
    vector<unique_ptr<const CityFactory>> cityFactories{};
    cityFactories.emplace_back(make_unique<CityFactory_Grid>());
    return cityFactories;
}

const vector<unique_ptr<const ResidentsFactory>> initResidentFactories()
{
    vector<unique_ptr<const ResidentsFactory>> residentFactories = {};
    residentFactories.emplace_back(make_unique<const ResidentsFactory_Falling>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_Flat>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_Rising>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_StepDown>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_StepUp>());
    return residentFactories;
}