#ifndef SIMULATOR_E_H
#define SIMULATOR_E_H

#include "Resident.h"
#include "City.h"
#include <vector>
#include <map>
#include <set>
#include <utility>

class Simulator_E
{
    private:
        City* _city;
        std::vector<Resident*> _residents;
        std::map<House*, Resident*> _curr_house_to_res_map = {};
        std::map<Resident*, House*> _curr_res_to_house_map = {};
        bool firstSimDone = false;

        // selectRandom deletes the integer that is returned from @setOfInt
        int selectRandom (std::set<int>& setOfInts) const;
        House* selectRandom (std::set<House*>& setOfHouses) const;
        void firstSimulation ();
        std::set<House*> getSetOfHouses ();
        std::set<int> getSetOfInts (int max);
        std::pair<std::vector<int>, std::vector<int>> getMovingResIdxs ();
        std::vector<Resident*> getResidents (std::vector<int> residentIndices);
        std::map<Resident*, House*> getHouses(std::vector<Resident*> residents);
        void openHouses (std::vector<Resident*> residents);
        std::set<House*> filterForOpenHouses (std::set<House*> houses);
        House* findHouseForForcedResHappyAtGoal (
            Resident* res,
            House* oldHouse,
            std::set<House*> openHouses // open houses within distance of resident
        );
        House* findHouseForForcedResHappyAtBest (
            Resident* res,
            House* oldHouse,
            std::set<House*> openHouses // open houses within distance of resident
        );
        House* findHouseForOptionalMoveRes (
            Resident* res,
            House* oldHouse,
            std::set<House*> openHouses, // open houses within distance of resident
            int chances
        );
        std::set<House*> getKeysFromMap (std::map<House*, Resident*> theMap);
        House* findHomeForForcedToMoveResident (
            Resident* resident, 
            House* oldHouse, 
            int count
        );
        House* findHomeForOptionalMoveResident (
            Resident* resident, 
            House* oldHouse, 
            int count
        );

        // Returns the neighbors for each house in @houses.
        std::map<House*, std::set<House*>> getSetsOfNeighbors (std::set<House*> houses);

        void moveResidentIntoHouse (Resident* res, House* house);
        void openHouse (Resident* res);
        std::set<Resident*> getResidentsInHouses (std::set<House*> houses);

    public:
        Simulator_E (City* city, std::vector<Resident*> residents);
        Simulator_E () = delete;
        Simulator_E (const Simulator_E& o) = default;
        Simulator_E (Simulator_E&& o) noexcept = default;
        Simulator_E& operator= (const Simulator_E& o) = default;
        ~Simulator_E () = default;
        std::map<House*, Resident*> simulate();

};

#endif