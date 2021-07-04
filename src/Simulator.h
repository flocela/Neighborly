#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Resident.h"
#include "City.h"
#include <vector>
#include <map>
#include <set>
#include <utility>

class Simulator
{
    private:
        City* _city;
        std::vector<Resident*> _residents;
        std::map<int, Resident*> _curr_addr_to_res_map = {};
        bool firstSimDone = false;

        // selectRandom deletes the integer that is returned from @setOfInt
        int selectRandom (std::set<int>& setOfInt) const;
        void firstSimulation ();
        std::set<int> getSetOfAddresses ();
        std::set<int> getSetOfInts (int max);
        std::pair<std::vector<int>, std::vector<int>> getMovingResIdxs ();
        std::vector<Resident*> getResidents (std::vector<int> residentIndices);
        std::map<Resident*, int> getAddresses(std::vector<Resident*> residents);
        void openHouses (std::vector<Resident*> residents);
        std::set<int> filterForOpenHouses (std::set<int> addresses);
        int findAddressForForcedRes (
            Resident* resident,
            int oldAddress,
            std::set<int> openHouses, // open houses within distance of resident
            int chances
        );
        int findAddressForForcedResHappyAtGoal (
            Resident* res,
            int oldAddress,
            std::set<int> openHouses // open houses within distance of resident
        );
        int findAddressForForcedResHappyAtBest (
            Resident* res,
            int oldAddress,
            std::set<int> openHouses // open houses within distance of resident
        );
        int findAddressForOptionalMoveRes (
            Resident* res,
            int oldAddress,
            std::set<int> openHouses, // open houses within distance of resident
            int chances
        );
        std::vector<Color> getColors (std::vector<int> addresses);
        std::set<int> getKeysFromMap (std::map<int, Resident*> theMap);

    public:
        Simulator (City* city, std::vector<Resident*> residents);
        Simulator () = delete;
        Simulator (const Simulator& o) = default;
        Simulator (Simulator&& o) noexcept = default;
        Simulator& operator= (const Simulator& o) = default;
        ~Simulator () = default;
        std::map<int, Resident*> simulate();

};

#endif