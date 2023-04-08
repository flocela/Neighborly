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
    {   
        firstRun();
        _first_run_done = true;
    }
    else
    {   chrono::high_resolution_clock::time_point WW = chrono::high_resolution_clock::now();
        normalRun();
        ++runNum;
        chrono::high_resolution_clock::time_point XX = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(XX-WW).count(); (void)duration;
        if (runNum == 6 || runNum == 7)
            {cout << "run XX-WW: " << duration << "; ";}
    }
    
    chrono::high_resolution_clock::time_point UU = chrono::high_resolution_clock::now();
    setHappinessValuesForAllResidents();
    chrono::high_resolution_clock::time_point VV = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(VV-UU).count(); (void)duration;
        if (runNum == 6)
            {cout << "set happiness VV-UU: " << duration << "; ";}

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
    chrono::high_resolution_clock::time_point QQ = chrono::high_resolution_clock::now();
    unordered_set<int> chosenResidents{};
    // make a copy of the set or residents (copy needed to randomly choose residents)
    vector<Resident*> copySetOfResidents{};
    for (Resident* res : _residents)
    {
        copySetOfResidents.push_back(res);
    }

    chrono::high_resolution_clock::time_point RR = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(RR-QQ).count();
    if (runNum == 6)
        {cout << "create vector Of residents: " << duration << "; ";}

    int subsetToMove = _residents.size() * _percent_of_residents /100;
    if (runNum == 6)
    {cout <<"subsetToMove: " << _residents.size() << ", " << subsetToMove << ", ";}

    // find a house for each randomly chosen resident.
    for (int ii=0; ii<subsetToMove; ++ii)
    {   
        chrono::high_resolution_clock::time_point YY = chrono::high_resolution_clock::now();
        Resident* curRes = selectRandom(copySetOfResidents); // make new setOfResidents if finding is 1/4
        //TODO makes curRes isn't being deleted.
        while ( chosenResidents.find(curRes->getID()) != chosenResidents.end() )
        {
            curRes = selectRandom(copySetOfResidents);
        }
        chosenResidents.insert(curRes->getID());
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
         {cout << "res:" << curRes->getID() << ", ";}

        chrono::high_resolution_clock::time_point ZZ = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(ZZ-YY).count(); (void)duration;
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
            {cout << "randomly select resident ZZ-YY: " << duration << "; ";}

        const House* currHouse = _house_per_resident[curRes];

        int print = (runNum ==6 && curRes->getID() < 10800 && curRes->getID() > 10780)? 6 : 0;

        chrono::high_resolution_clock::time_point AA = chrono::high_resolution_clock::now();
       
        const unordered_set<const House*>& allHousesWithinDistance = _city->getHousesWithinDistance
        (   
            currHouse,
            curRes->getAllowedMovementDistance(),
            print
        );
        
        chrono::high_resolution_clock::time_point BB = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(BB-AA).count();
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "getAllHousesWithinDist BB-AA: " << duration << "; ";}
            
        chrono::high_resolution_clock::time_point CC = chrono::high_resolution_clock::now();

        // emptyHouses vector should only have houses that are empty.
        vector<const House*> emptyHouses{};
        
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        {
            cout << "openHouses, allHousesWithinDist: " << _open_houses.size()
            << ", " << allHousesWithinDistance.size() << endl;
        }
        if (_open_houses.size() < allHousesWithinDistance.size())
        {
            unordered_set<const House*>::const_iterator iter = _open_houses.cbegin();
            while (iter != _open_houses.end())
            {   
                // if house within distance
                if (allHousesWithinDistance.find(*iter) != allHousesWithinDistance.end())
                {   
                    emptyHouses.push_back(*iter);
                }
                ++iter;
            }
        }
        else
        {   
            unordered_set<const House*>::const_iterator iter = allHousesWithinDistance.cbegin();
            while (iter != allHousesWithinDistance.end())
            {   
                // if house is empty
                if (_open_houses.find(*iter) != _open_houses.end())
                {   
                    emptyHouses.push_back(*iter);
                }
                ++iter;
            }
        }
        
        

        chrono::high_resolution_clock::time_point DD = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(DD-CC).count();
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "Remove occupied houses DD - CC: " << duration << "; ";}

        chrono::high_resolution_clock::time_point EE = chrono::high_resolution_clock::now();
        // try to find house for current resident. Only get _max_num_of_tries_to_find_house.
        double selectedHappiness = 0.0;
        House const * selectedHouse = nullptr;
        unordered_set<const House*> selectedHouses{};
        int maxTries = min(_max_num_of_tries_to_find_house, (int)emptyHouses.size());
        // TODO if max num of tries is 1/2 or greater than emptyHouses.size(), then use a set 
        // instead of a vector.
        //cout << "{maxtries, emptyHouses.size}: " << _max_num_of_tries_to_find_house << ", "
        //<< emptyHouses.size() << ";   "; 
        for (int ii=0; ii<maxTries; ++ii)
        {
            // choose a random house that has not been chosen before.
            const House* randHouse = selectRandom(emptyHouses); 
            // TODO check for nullptr, check for vector being size zero
            while (selectedHouses.find(randHouse) != selectedHouses.end())
            {
                randHouse = selectRandom(emptyHouses);
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
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "Found a house: FF - EE: " << duration << ", ";}

        chrono::high_resolution_clock::time_point GG = chrono::high_resolution_clock::now();
        if (selectedHouse != nullptr)
        {
            moveResidentIntoHouse(curRes, selectedHouse);
        }

        chrono::high_resolution_clock::time_point HH = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(HH-GG).count();
        if (runNum == 6 && curRes->getID() < 10800 && curRes->getID() > 10780)
        {cout << "mvoed: GG - HH: " << duration << endl;}

    }
}

void Simulator_Basic_B::moveResidentIntoHouse (Resident* res, const House* newHouse)
{   
    if (_house_per_resident.find(res) != _house_per_resident.end())
    {
        const House* oldHouse = _house_per_resident[res];
        _house_per_resident.erase(res);
        _res_per_house.erase(oldHouse);
        _open_houses.insert(oldHouse);
    }
    _res_per_house.insert(pair<const House*, Resident*>(newHouse, res));
    _house_per_resident.insert(pair<Resident*, const House*>(res, newHouse));
    _open_houses.erase(newHouse);
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