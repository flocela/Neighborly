#ifndef SIMULATOR_Basic_B_H
#define SIMULATOR_BASIC_B_H

#include "City.h"

#include <map>
#include <memory>
#include <unordered_set>
#include "CityState.h"
#include "Simulator.h"


class Simulator_Basic_B: public Simulator
{
public:
    Simulator_Basic_B (
        const City* city,
        std::unordered_set<Resident*> residents,
        double percentOfResidents, // percent of residents that are chosen to move each run.
        int numOfHousesChosen, // number of houses the residents can choose from
        std::unique_ptr<CityState> cityState
    );
    Simulator_Basic_B () = delete;
    Simulator_Basic_B (const Simulator_Basic_B& o) = default;
    Simulator_Basic_B (Simulator_Basic_B&& o) noexcept = default;
    Simulator_Basic_B& operator= (const Simulator_Basic_B& o) = default;
    Simulator_Basic_B& operator= (Simulator_Basic_B&& o) noexcept = default;
    ~Simulator_Basic_B () = default;

    // simulates one run (or round).
    // A run is: Randomly take percentage of residents and try to move them into a new house.
    // Randomly take a number of empty houses that are within the resident's allowable moving
    // distance (the resident's current home is not included).
    // Move the resident into the house that makes them the happiest.
    // If there is no empty houses that are within the allowable moving distance, then the
    // resident will not move.
    // ResidentA may move to a house that makes them happy, then subsequently residentB
    // may move next to the residentA. This could result in changing residentA's happiness,
    // making them happier or unhappy. 
    std::unordered_map<const House*, const Resident*> run() override;

    std::string toString() override;

private:
    const City* _city;
    bool _first_run_done = false;

    // all residents
    std::unordered_set<Resident*> _residents;

    // Percent of residents that will be forced to move at each run. They don't have
    // to move if there's no empty houses within their allowed movement distance.
    double _percent_of_residents = 30;

    // Number of randomly houses resident chosen. Resident will choose from these houses
    int _max_num_of_tries_to_find_house = 30;

    // in first run, no resident has a house. And all residents are assigned a house.
    void firstRun ();

    // all runs which aren't the first run
    void normalRun ();

    //TODO delte just here for timeing
    int runNum = 0;

    std::unique_ptr<CityState> _city_state;

    std::vector<Resident*> _moving_residents_vector;

    std::unordered_set<Resident*> _residents_chosen_from_cur_vector;

    std::vector<const House*> _open_houses_vector;
    

    // Will try to move the resident into a random available house.
    // An available house is an empty house, within the resident's allowable movement distance.
    // If there are no available houses which will make the resident happy (hapiness greater
    // or equal to happiness goal), then the resident will not be moved.
    // Will randomly try available houses. If a house that will make the resident
    // happy is not found within numOfTries, then the resident will not be moved.
    void moveResident (Resident* res, int numOfTries);

    void setHappinessValuesForAllResidents();

    double calculateHappinessValueFor(Resident* res, int address);

    Resident* chooseResident ();

    void resetMovingResidentsVector ();

    void updateMovingResidentsVector ();

};

#endif