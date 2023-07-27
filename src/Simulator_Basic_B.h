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

    // Simulates one run (or round).
    // A run is made of randomly taking a percentage of residents and trying to move each of them
    // into a new house that was randomly chosen.
    // To choose a house randomly, first take a number of empty houses that are within the
    // resident's allowable moving distance (the resident's current home is not included).
    // Randomly go through each house and find the one that makes the resident the
    // happiest. If there is a tie (as to happiest house), then the house that was found first
    // is chosen.
    // If there is no empty houses that are within the allowable moving distance, then the
    // resident will not move.
    // If the house that is chosen to make the resident happiest still does not make
    // the resident happy (resident's happiness is less than resident's happiness goal)
    // then do not move the resident.
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

    // All runs which aren't the first run.
    // Randomly select a _percent_of_residents to be moved. In random order, go through
    // chosen residents and try to move them into an available house.
    // An available house is an empty house, within the resident's allowable movement distance.
    // If there are no available houses which will make the resident happy (happiness greater
    // or equal to happiness goal), then the resident will not be moved.
    // Will randomly try available houses. If a house that will make the resident
    // happy is not found within numOfTries, then the resident will not be moved.
    void normalRun ();

    void setHappinessValuesForAllResidents();

    double calculateHappinessValueFor(Resident* res, int address) const;

};

#endif