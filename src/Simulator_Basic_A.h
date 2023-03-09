#ifndef SIMULATOR_Basic_A_H
#define SIMULATOR_BASIC_A_H

#include <set>

#include "City.h"
#include "Simulator.h"


class Simulator_Basic_A: public Simulator
{
public:
    // @residents are all the residents in the city.
    Simulator_Basic_A (const City* city, std::set<Resident*> residents);
    Simulator_Basic_A () = delete;
    Simulator_Basic_A (const Simulator_Basic_A& o) = default;
    Simulator_Basic_A (Simulator_Basic_A&& o) noexcept = default;
    Simulator_Basic_A& operator= (const Simulator_Basic_A& o) = default;
    Simulator_Basic_A& operator= (Simulator_Basic_A&& o) noexcept = default;
    ~Simulator_Basic_A () = default;

    // simulates one run (or round). 
    // A run is: Take all residents that are unhappy. Then for each resident,
    // try to move them to a new house.
    // Trying to move them to a new house means:
    // 2. Randomly choose empty houses that are within the resident's allowable movement distance.
    // 3. See if that house will make them happy. If so, then move them.
    // 4. Will only try so many houses, (see _num_of_tries) before giving up.
    //    Then the resident won't move.
    // 5. It may be the case that there are no empty houses within the allowable movement distance.
    //    It may be that none of the empty houses within the allowable movement distance will make
    //    the resident happy. In which case, the resident will not move.
    // ResidentA may move to a house that makes them happy, then subsequently residentB
    // may move next to the residentA. This could result in changing residentA's happiness,
    // making them happier or unhappy. 
    std::unordered_map<const House*, Resident*> run() override;

    std::string toString() override;

private:
    const City* _city;
    bool _first_run_done = false;

    // all residents
    std::set<Resident*> _residents;

    // only houses that are occupied and their residents
    std::unordered_map<const House*, Resident*> _res_per_house = {};

    // only residents that have houses and their houses
    std::unordered_map<Resident*, const House*> _house_per_resident;

    // all unoccupied houses
    std::unordered_set<const House*> _open_houses;

    // Number of houses resident will try before, giving up and not moving on this run.
    int _num_of_tries = 40;

    // in first run, no resident has a house. And all residents are assigned a house.
    void firstRun ();

    // all runs which aren't the first run
    void normalRun ();

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
    std::set<Resident*> getResidentsInTheseHouses(std::set<const House*> houses);
};

#endif