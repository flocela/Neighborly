#ifndef SIMULATOR_BASIC_B_H
#define SIMULATOR_BASIC_B_H

#include <memory>
#include <unordered_set>
#include <vector>
#include "City.h"
#include "CityState.h"
#include "Simulator.h"

// Performs the simulation per run. See run() method to see how each run is performed.
class Simulator_Basic_B: public Simulator
{
public:
    Simulator_Basic_B (
        const City* city,
        std::unordered_set<Resident*> residents,
        double percentOfResidents, // percent of residents that are chosen to move each run.
        int numOfHousesToChooseFrom, // number of houses the residents can choose from
        std::unique_ptr<CityState> cityState
    );
    Simulator_Basic_B () = delete;
    Simulator_Basic_B (const Simulator_Basic_B& o) = default;
    Simulator_Basic_B (Simulator_Basic_B&& o) noexcept = default;
    Simulator_Basic_B& operator= (const Simulator_Basic_B& o) = default;
    Simulator_Basic_B& operator= (Simulator_Basic_B&& o) noexcept = default;
    ~Simulator_Basic_B () noexcept = default;

    // In the first run, randomly assign each resident a house.
    // For all subsequent runs:
    // Randomly select a _percent_of_residents to be moved. In random order, go through
    // selected residents and try to move them into an available house.
    // An available house is an empty house within the resident's allowable movement distance.
    // Try the available houses in random order. Find the house that would make the resident
    // happiest. If there is a tie as to which house would make the resident happiest,
    // the first randomly chosen house is selected.
    // If none of the houses make the resident happy (happiness greater or equal to the resident's
    // happiness goal, then the resident will not be moved. If there are no available houses
    // within the resident's allowed movement distance, then the resident is not moved.
    // Note, ResidentA may move to a house that makes them happy, then subsequently residentB
    // may move next to the residentA. This could result in changing residentA's happiness,
    // making them happier or sadder. 
    ResPerHouse run() override;

    std::string toString() override;

private:
    const City* _city;

    // Percent of residents that will be forced to move at each run.
    double _percent_of_residents = 30;

    // Number of houses randomly chosen by a resident. Resident will choose from these houses.
    int _max_num_of_tries_to_find_house = 30;

    // The state of the city. (Mostly where each resident lives in the city.)
    std::unique_ptr<CityState> _city_state;

    // All residents, sorted.
    std::vector<Resident*> _sorted_residents{};

    // At the begining of the first run no resident has a house. They are randomly assigned a house
    // in first run.
    void firstRun ();

    // normal run is all runs that aren't the first run. See run() for how a normal 
    // progresses.
    void normalRun ();

    void setHappinessValuesForAllResidents();

    double calculateHappinessValueFor(Resident* res, int address) const;

};

#endif