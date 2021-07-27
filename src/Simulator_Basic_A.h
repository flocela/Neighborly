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

        std::map<House*, Resident*> simulate() override;
    
    private:
        City* _city;
        bool _first_simulation_done = false;

        // All residents
        std::set<Resident*> _residents;

        // Only houses that are occupied and their residents
        std::map<House*, Resident*> _curr_house_to_res_map = {};

        // Only residents that have houses and their houses
        std::map<Resident*, House*> _curr_res_to_house_map;

        // All unoccupied houses
        std::set<House*> _open_houses;

        // In first simulation, no resident has a house. And all residents are assigned a house.
        void firstSimulation ();

        // Will move the resident into a random house, if currently,
        // their happiness is less than their happiness goal.
        // The random house may be farther than the distance that the 
        // @res can travel.
        void moveResidentIfUnhappy (Resident* res);

        // @res is the resident. @newHouse is the new house @res will be moved to.
        // @newHouse is assumed to be currently unoccupied, is in _open_houses set.
        // If @res has a current house, removes @res and that house from the
        // _curr_house_to_res_map and the _curr_res_to_house_map.
        // Adds the house (now the old house) into the _open_houses set.
        // Then adds @res and @newHouse into said maps.
        // Removes @newHouse from _open_houses.
        void moveResidentIntoHouse (Resident* res, House* newHouse);

        void updateResident (Resident* res);

        // Returns residents that live in @houses. If a house is empty, then 
        // returned set will be smaller than @houses.
        std::set<Resident*> getResidentsInHouses(std::set<House*> houses);
        House* selectRandom (std::set<House*>& setOfHouses) const;
        
};

#endif