#include "Simulator_Basic_B.h"

#include <algorithm>
#include <limits>
#include <chrono> // TODO delete include chrono
using namespace std;

template <typename T>
T selectRandom(unordered_set<T>& setOfT)
{
    int size = setOfT.size();
    int r = rand() % size;
    auto it = setOfT.begin();
    advance(it,r);
    return *it;
}

template <typename T>
T selectRandom(vector<T>& vectorOfT)
{
    int size = vectorOfT.size();
    int r = rand() % size;
    return vectorOfT[r];
}

Simulator_Basic_B::Simulator_Basic_B (
    const City* city,
    unordered_set<Resident*> residents,
    double percentOfResidents,
    int numOfHousesChosen
): _city{city},
   _residents{residents},
   _percent_of_residents{percentOfResidents},
   _max_num_of_tries_to_find_house{numOfHousesChosen}
{
    // to begin with, all houses are empty
    for (const House* house : _city->getHouses())
    {   
        _open_houses.insert(house);
    }
}

std::unordered_map<const House*, Resident*> Simulator_Basic_B::run ()
{
    if (!_first_run_done)
    {   cout << "first run" << endl;
        firstRun();
        _first_run_done = true;
    }
    else
    {   cout << "else runNum: " << runNum << endl;
        chrono::high_resolution_clock::time_point WW = chrono::high_resolution_clock::now();
        normalRun();
        chrono::high_resolution_clock::time_point XX = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(XX-WW).count(); 
        if (runNum == 6 || runNum == 1)
            {cout << "run XX-WW: " << duration << "; ";}
        
    }
    
    chrono::high_resolution_clock::time_point UU = chrono::high_resolution_clock::now();
    setHappinessValuesForAllResidents();
    chrono::high_resolution_clock::time_point VV = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(VV-UU).count();
        if (runNum == 6 || runNum == 1)
            {cout << "set happiness VV-UU: " << duration << "; ";}

    ++runNum;
    
    return _res_per_house;
}

string Simulator_Basic_B::toString()
{
    return "Simulator Basic B";
}

void Simulator_Basic_B::firstRun ()
{
    // make a copy of the set or residents (copy is needed to randomly choose residents)
    unordered_set<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.insert(res);
    }

    // for each resident, choose a random house.
    while (copySetOfResidents.size() != 0)
    {   
        Resident* randRes = selectRandom(copySetOfResidents);

        const House* house = selectRandom(_open_houses);
        
        _res_per_house.insert({house, randRes});
        
        _house_per_resident.insert({randRes, house});
        
        _open_houses.erase(house);

        copySetOfResidents.erase(randRes);
    }
}

void Simulator_Basic_B::normalRun ()
{
    //chrono::high_resolution_clock::time_point QQ = chrono::high_resolution_clock::now();
    unordered_set<int> chosenResidents{};
    // make a copy of the set or residents (copy needed to randomly choose residents)
    vector<Resident*> vectorOfResidents{};
    for (Resident* res : _residents)
    {
        vectorOfResidents.push_back(res);
    }

    //chrono::high_resolution_clock::time_point RR = chrono::high_resolution_clock::now();
    //auto duration = chrono::duration_cast<chrono::microseconds>(RR-QQ).count();
    //if (runNum == 6)
    //    {cout << "create vector Of residents: " << duration << "; ";}

    int numOfResToMove = _residents.size() * _percent_of_residents /100;
    //if (runNum == 6)
    //{cout <<"subsetToMove: " << _residents.size() << ", " << subsetToMove << ", ";}

    // find a house for each randomly chosen resident.
    for (int ii=0; ii<numOfResToMove; ++ii)
    {   
        //chrono::high_resolution_clock::time_point YY = chrono::high_resolution_clock::now();
        Resident* curRes = selectRandom(vectorOfResidents); // make new setOfResidents if finding is 1/4
        //TODO makes curRes isn't being deleted.
        // resident can't be chosen twice in one run.
        while ( chosenResidents.find(curRes->getID()) != chosenResidents.end() )
        {
            curRes = selectRandom(vectorOfResidents);
        }
        chosenResidents.insert(curRes->getID());
        //if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        // {cout << "res:" << curRes->getID() << ", ";}

        //chrono::high_resolution_clock::time_point ZZ = chrono::high_resolution_clock::now();
        //auto duration = chrono::duration_cast<chrono::microseconds>(ZZ-YY).count(); (void)duration;
        //if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        //    {cout << "randomly select resident ZZ-YY: " << duration << "; ";}

        const House* currHouse = _house_per_resident[curRes];

        int print = ((runNum == 6|| runNum == 1) && curRes->getID() < 10800 && curRes->getID() > 10780)? 6 : 0;

        chrono::high_resolution_clock::time_point AA = chrono::high_resolution_clock::now();
       
        
        if ( _houses_within_distance.find(
             {curRes->getAllowedMovementDistance(), currHouse->getAddress()}) == 
             _houses_within_distance.end() )
        {
            _houses_within_distance[{curRes->getAllowedMovementDistance(),
                                     currHouse->getAddress()}] = 
            _city->getHousesWithinDistance(   
                currHouse,
                curRes->getAllowedMovementDistance(),
                print
                );
        }
        
        unordered_set<const House*>& allHousesWithinDistance =
            _houses_within_distance[{curRes->getAllowedMovementDistance(),
                                     currHouse->getAddress()}];
        chrono::high_resolution_clock::time_point BB = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(BB-AA).count();
        if ((runNum == 6 || runNum == 1) && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "getAllHousesWithinDist BB-AA: " << duration << "; ";}

        chrono::high_resolution_clock::time_point LL = chrono::high_resolution_clock::now();
        vector<const House*> vectorOpenHousesWithinDistance{};
        if (allHousesWithinDistance.size() < _open_houses.size())
        {
            for (auto h : allHousesWithinDistance)
            {
                if (_open_houses.find(h) != _open_houses.end())
                    vectorOpenHousesWithinDistance.push_back(h);
            }
        }
        else
        {
            for (auto h : _open_houses)
            {
                if (allHousesWithinDistance.find(h) != allHousesWithinDistance.end())
                    vectorOpenHousesWithinDistance.push_back(h);
            }
        }
        chrono::high_resolution_clock::time_point MM = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(MM-LL).count();
        if ((runNum == 6 || runNum == 1) && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "put houses into vector MM-LL: " << duration << "; ";}
    
        chrono::high_resolution_clock::time_point EE = chrono::high_resolution_clock::now();
        // try to find house for current resident. Only get _max_num_of_tries_to_find_house.
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;
        unordered_set<const House*> selectedHouses{};
        int maxTries = min(_max_num_of_tries_to_find_house, (int)vectorOpenHousesWithinDistance.size());
        // TODO if max num of tries is 1/2 or greater than emptyHouses.size(), then use a set 
        // instead of a vector.
        //cout << "{maxtries, emptyHouses.size}: " << _max_num_of_tries_to_find_house << ", "
        //<< emptyHouses.size() << ";   "; 
        for (int ii=0; ii<maxTries; ++ii)
        {
            // choose a random house that has not been chosen before.
            const House* randHouse = selectRandom(vectorOpenHousesWithinDistance); 
            // TODO check for nullptr, check for vector being size zero
            while (selectedHouses.find(randHouse) != selectedHouses.end())
            {
                randHouse = selectRandom(vectorOpenHousesWithinDistance);
            }

            double happinessFromRandomHouse = calculateHappinessValueFor(curRes, randHouse->getAddress());
            if (happinessFromRandomHouse >= selectedHappiness)
            {
                selectedHappiness = happinessFromRandomHouse;
                selectedHouse = randHouse;
            }
            if (selectedHappiness == curRes->getMaximumPossibleHappiness())
            {
                break;
            }
        }

        chrono::high_resolution_clock::time_point FF = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(FF-EE).count();
        if ((runNum == 6|| runNum == 1) && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "Found a house: FF - EE: " << duration << ", ";}

        //chrono::high_resolution_clock::time_point GG = chrono::high_resolution_clock::now();
        if (selectedHouse != nullptr)
        {
            moveResidentIntoHouse(curRes, selectedHouse);
        }

        //chrono::high_resolution_clock::time_point HH = chrono::high_resolution_clock::now();
        //duration = chrono::duration_cast<chrono::microseconds>(HH-GG).count();
        //if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        //{cout << "mvoed: GG - HH: " << duration << endl;}

    }
}

void Simulator_Basic_B::moveResidentIntoHouse (Resident* res, const House* newHouse)
{   
    //int res_per_house_sizeA = _res_per_house.size();
    //int house_per_resident_sizeA = _house_per_resident.size();
    //int open_houses_sizeA = _open_houses.size();

    if (_house_per_resident.find(res) != _house_per_resident.end())
    {
        const House* oldHouse = _house_per_resident[res];
        _house_per_resident.erase(res);
        //int resPerHousesizeA = _res_per_house.size();
        //if ( _res_per_house.find(oldHouse) == _res_per_house.end() ) {cout << "resperhouse can't find house";}
        _res_per_house.erase(oldHouse);
        //int resPerHousesizeB = _res_per_house.size();
        //if (resPerHousesizeA - resPerHousesizeB != 1){cout <<"resPerHouseSizeDiff: " << (resPerHousesizeB - resPerHousesizeA) << " ";}
        _open_houses.insert(oldHouse);
    }

    //if (_res_per_house.find(newHouse) != _res_per_house.end()) { cout << "_res_per_house insertion is not going to work;";}
    auto p = _res_per_house.insert(pair<const House*, Resident*>(newHouse, res));
    if (p.second == false)
    {
        cout << "_res_per_house insertion did not work.";
    }

    auto q = _house_per_resident.insert(pair<Resident*, const House*>(res, newHouse));
    if (q.second == false)
    {
        cout << "_house_per_resident insertion did not work.";
    }
    _open_houses.erase(newHouse);

/*
    int res_per_house_sizeB = _res_per_house.size();
    int house_per_resident_sizeB = _house_per_resident.size();
    int open_houses_sizeB = _open_houses.size();
    
    if (res_per_house_sizeA != res_per_house_sizeB) {
        cout << res_per_house_sizeA << "vs" << res_per_house_sizeB << " ";
    }

    if (house_per_resident_sizeA != house_per_resident_sizeB) {
        cout << house_per_resident_sizeA << "vs" << house_per_resident_sizeB << " ";
    }

    if (open_houses_sizeA != open_houses_sizeB) {
        cout << open_houses_sizeA << "vs" << open_houses_sizeB << " ";
    }*/
}

void Simulator_Basic_B::setHappinessValuesForAllResidents ()
{
    for (Resident* res : _residents)
    {
        const House* house = _house_per_resident[res];
        res->setHappiness(calculateHappinessValueFor(res, house->getAddress()));
    }
}

// todo res should be const.
double Simulator_Basic_B::calculateHappinessValueFor(Resident* res, int address)
{
    unordered_set<const House*> adjHouses = _city->getHousesAdjacent(address);
    unordered_set<const Resident*> residents;
    for (const House* house : adjHouses)
    {   
        if (_res_per_house.find(house) != _res_per_house.end())
        {
            residents.insert(_res_per_house[house]);
        } 
    }
    return res->calculateHappiness(residents, adjHouses.size());
}

//TODO no one is using this method, delete
unordered_set<const Resident*> Simulator_Basic_B::getResidentsInTheseHouses (
    unordered_set<const House*> houses)
{   
    unordered_set<const Resident*> residents;
    for (const House* house : houses)
    {   
        if (_res_per_house.find(house) != _res_per_house.end())
        {
            residents.insert(_res_per_house[house]);
        } 
    }
    return residents;
}