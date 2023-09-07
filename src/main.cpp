

/*
 * Original project is by Amine Ben Hassouna. It allowed the user to
 * write text and render blocks in a window. 
 * 
 * The idea of Neighborly, which is a simulation of two different
 * groups of residents living in a city and the effects on 
 * their happiness, is taken from the simulation "Parable
 * of the Polygons" at https://ncase.me/polygons. The code in this
 * version here is by Aurea F. Maldonado - 2023.
 * 
 * The copyright is the same as Amine Ben Hassouna's (2018 2019)
 * copyrights below.
 * 
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
#include <thread>

#include "CityFactory.h"
#include "CityFactory_Grid.h"
#include "CollectorByExamples.h"
#include "CollectorByQuestions.h"
#include "CollectorByInputFile.h"
#include "Printer_Graphic.h"
#include "Printer_CmdLine.h"
#include "Renderer_SDL.h"
#include "ResidentsFactory_Falling.h"
#include "ResidentsFactory_Flat.h"
#include "ResidentsFactory_Rising.h"
#include "ResidentsFactory_StepDown.h"
#include "ResidentsFactory_StepUp.h"
#include "ResPerHouse.h"
#include "Simulator.h"
#include "SimulationComponents.h"
#include "UI_CmdLine.h"
#include "UsePremadeExampleQuestion.h"

#define FONT_PATH "assets/pacifico/Pacifico.ttf"

using namespace std;

const vector<unique_ptr<const CityFactory>> initCityFactories ();
const vector<unique_ptr<const ResidentsFactory>> initResidentFactories ();
SimulationComponents createSimulationComponents (int argc, char* argv[]);

const int SCREEN_WIDTH = 2400;
const int SCREEN_HEIGHT = 1200;
const int MAX_HOUSES_X = 120;
const int MAX_HOUSES_Y = 120;
const int MAX_NUM_OF_RUNS = 200;

int main(int argc, char* argv[])
{   
    // components will be populated using a file, premade examples,
    // or user choices from the command line.
    // components and attributes within SimulationComponents are owned
    // by main. They are passed to other class' constructors by const reference,
    // const pointer, or by value.
    SimulationComponents components = createSimulationComponents(argc, argv);

    // CityPrinter cityPrinter is owned by main.
    // It is passed to Printer_CmdLine's constructor by const pointer.
    unique_ptr<CityPrinter> cityPrinter = make_unique<CityPrinter>(components.city.get());

    // Construct graphic printer
    Printer_Graphic graphicPrinter{
        make_unique<Renderer_SDL>(SCREEN_WIDTH, SCREEN_HEIGHT,"Neighbors"),
        components.baseColorsPerGroupid,
        *(components.city->getCoordinatesPerHouse()),
        *(components.city->getAdjacentHousesPerHouse()),
        "Neighbors",
        components.numOfRuns
    };

    // Construct cmd line printer
    Printer_CmdLine cmdLinePrinter{
        *(cityPrinter.get()),
        components.baseColorsPerGroupid,
        components.residentTemplatePerGroupId,
        components.numOfRuns,
        components.randomSeed,
        components.simulator->toString()
    };

    // Set seed for randomization for simulation.
    srand(components.randomSeed);

    // Start simulation. Simulation runs in a for-loop. Each loop is a run.
    // runMetrics is updated after each run. Results are printed after each run.
    RunMetrics runMetrics{*(components.city->getAdjacentHousesPerHouse())};

    for (int ii=0; ii<components.numOfRuns; ii++)
    {  
        ResPerHouse residentsPerHouse = components.simulator->run();
        runMetrics.updateMetrics(ii, move(residentsPerHouse));

        // every run should show for at least 1/4 second
        auto timeStart = std::chrono::high_resolution_clock::now();
        
        graphicPrinter.print(&runMetrics);
        
        cmdLinePrinter.print(&runMetrics);

        // show results for at least 1/4 second.
        std::this_thread::sleep_until(timeStart + std::chrono::milliseconds(250));
    }

    // Print out empty output if there are zero runs.
    if (components.numOfRuns == 0)
    {
        graphicPrinter.print(&runMetrics);
        cmdLinePrinter.print(&runMetrics);
    }

    graphicPrinter.lastPrint();
    cmdLinePrinter.lastPrint();

    return 0; 
}

// Create simulation components.
// Pass in arguments from main. If argv[1] contains a file name, then simulation components
// are made from the file name. Otherwise user is asked if they want to choose
// from premade examples or create simulation components from a series of questions on the command line.
SimulationComponents createSimulationComponents (int argc, char* argv[])
{
    SimulationComponents components;

    bool usingFile = (argc >= 2);

    if (usingFile)
    {
        string inputFile = argv[1];
        CollectorByInputFile collectorByInputFile{};
        components = collectorByInputFile.createSimulationComponents("../" + inputFile);
    }
    else
    {   
        // Gather information from user using the cmd line
        const UI_CmdLine cmdLine{};

        // User chooses to use pre-made examples, or type in required information.
        UsePremadeExampleQuestion usePremadeExamplesQuestion;
        bool usingExamples = usePremadeExamplesQuestion.askUser(cmdLine);

        if (usingExamples)
        {   
            CollectorByExamples collectorByExamples;
            components = collectorByExamples.createSimulationComponents(cmdLine);
        }
        else
        {
            CollectorByQuestions collectorByQuestions{};
            components = collectorByQuestions.createSimulationComponents(
                cmdLine,
                initCityFactories(),
                initResidentFactories(),
                MAX_HOUSES_X,
                MAX_HOUSES_Y,
                MAX_NUM_OF_RUNS
            );
        }
    }

    // Throw exception if it is plain that input errors were made.
    if (components.city->getNumOfHouses() < components.residents.size())
    {
        throw invalid_argument("Number of houses needs to be larger than number of residents.");
    }
    if (components.city->getNumOfHouses() == 0)
    {
        throw invalid_argument("City must have at least one house.");
    }
    if (components.residents.size() == 0)
    {
        throw invalid_argument("There must be at least one resident.");
    }
    
    return components;
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
    residentFactories.emplace_back(make_unique<const ResidentsFactory_Flat>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_Falling>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_Rising>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_StepDown>());
    residentFactories.emplace_back(make_unique<const ResidentsFactory_StepUp>());
    return residentFactories;
}