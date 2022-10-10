#ifndef SIMULATOR_E_H
#define SIMULATOR_E_H

#include "Resident.h"
#include "City.h"
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <unordered_set>

class Simulator_E
{
    private:
        City* _city;
        std::vector<Resident*> _residents;
        std::unordered_map<const House*, Resident*> _curr_house_to_res_map = {};
        std::map<Resident*, const House*> _curr_res_to_house_map = {};
        bool firstSimDone = false;

        // selectRandom deletes the integer that is returned from @setOfInt
        int selectRandom (std::set<int>& setOfInts) const;
        const House* selectRandom (std::set<const House*>& setOfHouses) const;
        void firstSimulation ();
        std::set<const House*> getSetOfHouses ();
        std::set<int> getSetOfInts (int max);
        std::pair<std::vector<int>, std::vector<int>> getMovingResIdxs ();
        std::vector<Resident*> getResidents (std::vector<int> residentIndices);
        std::unordered_map<Resident*, const House*> getHouses(std::vector<Resident*> residents);
        void openHouses (std::vector<Resident*> residents);
        std::unordered_set<House*> filterForOpenHouses (std::unordered_set<House*> houses);
        const House* findHouseForForcedResHappyAtGoal (
            Resident* res,
            House* oldHouse,
            std::set<const House*> openHouses // open houses within distance of resident
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
        std::set<const House*> getKeysFromMap (std::unordered_map<const House*, Resident*> theMap);
        const House* findHomeForForcedToMoveResident (
            Resident* resident, 
            const House* oldHouse, 
            int count
        );
        const House* findHomeForOptionalMoveResident (
            Resident* resident, 
            House* oldHouse, 
            int count
        );

        // Returns the neighbors for each house in @houses.
        std::map<const House*, std::set<const House*>> getSetsOfNeighbors (std::unordered_set<House*> houses);

        void moveResidentIntoHouse (Resident* res, const House* house);
        void openHouse (Resident* res);
        std::set<Resident*> getResidentsInHouses (std::set<const House*> houses);

    public:
        Simulator_E (City* city, std::vector<Resident*> residents);
        Simulator_E () = delete;
        Simulator_E (const Simulator_E& o) = default;
        Simulator_E (Simulator_E&& o) noexcept = default;
        Simulator_E& operator= (const Simulator_E& o) = default;
        ~Simulator_E () = default;
        std::unordered_map<const House*, Resident*> simulate();

};

#endif