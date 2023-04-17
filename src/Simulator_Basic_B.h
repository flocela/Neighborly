#ifndef SIMULATOR_Basic_B_H
#define SIMULATOR_BASIC_B_H

#include "City.h"

#include <map>
#include "Simulator.h"


class Simulator_Basic_B: public Simulator
{
public:
    Simulator_Basic_B (
        const City* city,
        std::unordered_set<Resident*> residents,
        double percentOfResidents, // percent of residents that are chosen to move each run.
        int numOfHousesChosen // number of houses the residents can choose from
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
    std::unordered_map<const House*, Resident*> run() override;

    std::string toString() override;

private:
    const City* _city;
    bool _first_run_done = false;

    // all residents
    std::unordered_set<Resident*> _residents;

    // only houses that are occupied and their residents
    std::unordered_map<const House*, Resident*> _res_per_house = {};

    // only residents that have houses and their houses
    std::unordered_map<Resident*, const House*> _house_per_resident;

    // all unoccupied houses
    std::unordered_set<const House*> _open_houses;

    // Percent of residents that will be forced to move at each run. They don't have
    // to move if there's no empty houses within their allowed movement distance.
    double _percent_of_residents = 10;

    // Number of randomly houses resident chosen. Resident will choose from these houses
    int _max_num_of_tries_to_find_house = 10;


    // in first run, no resident has a house. And all residents are assigned a house.
    void firstRun ();

    // all runs which aren't the first run
    void normalRun ();

    //TODO delte just here for timeing
    int runNum = 0;

    // Will try to move the resident into a random available house.
    // An available house is an empty house, within the resident's allowable movement distance.
    // If there are no available houses which will make the resident happy (hapiness greater
    // or equal to happiness goal), then the resident will not be moved.
    // Will randomly try available houses. If a house that will make the resident
    // happy is not found within numOfTries, then the resident will not be moved.
    void moveResident (Resident* res, int numOfTries);

    // @res is the resident. @newHouse is the new house @res will be moved to.
    // @newHouse is assumed to be currently unoccupied (is in _open_houses set).
    // If @res has a current house, removes @res and that house from the
    // _curr_house_to_res_map and the _curr_res_to_house_map.
    // Adds the house (now the old house) into the _open_houses set.
    // Then adds @res and @newHouse into said maps.
    // Removes @newHouse from _open_houses.
    void moveResidentIntoHouse (Resident* res, const House* newHouse);

    void setHappinessValuesForAllResidents();

    double calculateHappinessValueFor(Resident* res, int address);

    // Returns residents that live in @houses. If a house is empty, then 
    // returned set will be smaller than @houses.
    std::unordered_set<const Resident*> getResidentsInTheseHouses(
        std::unordered_set<const House*> houses
    );

    std::map< std::pair<double, int>, std::unordered_set<const House*> >
        _houses_within_distance;

};

#endif