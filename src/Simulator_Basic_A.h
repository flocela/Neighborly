#ifndef SIMULATOR_Basic_A_H
#define SIMULATOR_BASIC_A_H

#include "Simulator.h"
#include "City.h"
#include <set>

class Simulator_Basic_A: public Simulator
{
    public:
        // @residents are all the residents in the city.
        Simulator_Basic_A (City* city, std::set<Resident*> residents);
        Simulator_Basic_A () = delete;
        Simulator_Basic_A (const Simulator_Basic_A& o) = default;
        Simulator_Basic_A (Simulator_Basic_A&& o) noexcept = default;
        Simulator_Basic_A& operator= (const Simulator_Basic_A& o) = default;
        ~Simulator_Basic_A () = default;

        std::unordered_map<const House*, Resident*> simulate() override;
    
    private:
        City* _city;
        bool _first_simulation_done = false;

        // All residents
        std::set<Resident*> _residents;

        // Only houses that are occupied and their residents
        std::unordered_map<const House*, Resident*> _res_per_house_map = {};

        // Only residents that have houses and their houses
        std::unordered_map<Resident*, const House*> _house_per_resident_map;

        // All unoccupied houses
        std::unordered_set<const House*> _open_houses;

        // resident looks at count random houses when moving before giving up and not moving.
        int _count = 40;

        // In first simulation, no resident has a house. And all residents are assigned a house.
        void firstSimulation ();

        // Will move the resident into a random house, if currently,
        // their happiness is less than their happiness goal.
        // The random house may be farther than the distance that the 
        // @res can travel.
        void moveResident (Resident* res);

        // @res is the resident. @newHouse is the new house @res will be moved to.
        // @newHouse is assumed to be currently unoccupied, is in _open_houses set.
        // If @res has a current house, removes @res and that house from the
        // _curr_house_to_res_map and the _curr_res_to_house_map.
        // Adds the house (now the old house) into the _open_houses set.
        // Then adds @res and @newHouse into said maps.
        // Removes @newHouse from _open_houses.
        void moveResidentIntoHouse (Resident* res, const House* newHouse);

        // Returns residents that live in @houses. If a house is empty, then 
        // returned set will be smaller than @houses.
        std::set<Resident*> getResidentsInTheseHouses(std::set<const House*> houses);
        const House* selectRandom (std::unordered_set<const House*>& setOfHouses) const;

        const House* _get_res_cur_house (Resident* res);
        Resident* getCurrResident (const House* house);
        bool hasResident (const House* house);
        bool hasHouse (Resident* res);

        void setHappinessValuesForAllResidents();
        double calculateHappinessValueFor(Resident* res, int address);
        
};

#endif