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
        std::set<Resident*> _residents;
        std::map<House*, Resident*> _curr_house_to_res_map = {};
        std::map<Resident*, House*> _curr_res_to_house_map;
        std::set<House*> _open_houses;
        
        bool _first_simulation_done = false;
        void firstSimulation ();
        void moveResidentIfUnhappy (Resident* res);
        void moveResidentIntoHouse (Resident* res, House* house);
        std::set<Resident*> getResidentsInHouses(std::set<House*> houses);
        House* selectRandom (std::set<House*>& setOfHouses) const;
        
};

#endif