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
   _open_houses_per_y_x(_city->getHeight()+1,
                        vector<unordered_set<const House*>>(_city->getWidth()+1)),
    _percent_of_residents{percentOfResidents},
   _max_num_of_tries_to_find_house{numOfHousesChosen}
{
    // TODO reserve space for _open_houses_per_x_y
    // to begin with, all houses are empty
    for (const House* house : _city->getHouses())
    {   
        Coordinate xy = _city->getCoordinate(house->getAddress());
        int x = xy.getX();
        int y = xy.getY();
        _open_houses_per_y_x[y][x].insert(house);
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
        Coordinate coord = _city->getCoordinate(house->getAddress());

        _house_per_resident.insert({randRes, house});
        
        _open_houses.erase(house);
        _open_houses_per_y_x[_city->getCoordinate(house->getAddress()).getY()]
            [_city->getCoordinate(house->getAddress()).getX()].erase(house);

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

    // Find a house for each randomly chosen resident
    for (int ii=0; ii<numOfResToMove; ++ii)
    {   
        chrono::high_resolution_clock::time_point YY = chrono::high_resolution_clock::now();
        Resident* curRes = selectRandom(vectorOfResidents); // make new setOfResidents if finding is 1/4
        //TODO makes curRes isn't being deleted.
        // resident can't be chosen twice in one run.
        while ( chosenResidents.find(curRes->getID()) != chosenResidents.end() )
        {
            curRes = selectRandom(vectorOfResidents);
        }
        chosenResidents.insert(curRes->getID());

        chrono::high_resolution_clock::time_point ZZ = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(ZZ-YY).count(); (void)duration;
        if ( (runNum == 1 || runNum == 6) && curRes->getID() < 10800 && curRes->getID() > 10780)
            {cout << "randomly select resident ZZ-YY: " << duration << "; ";}

        const House* currHouse = _house_per_resident[curRes];

        //int print = ((runNum == 6|| runNum == 1) && curRes->getID() < 10800 && curRes->getID() > 10780)? 6 : 0;

        chrono::high_resolution_clock::time_point LL = chrono::high_resolution_clock::now();
        vector<const House*> vectorOpenHousesReduced{};
        pair<int, int> xRange = _city->getXRangeForAllowableDistanceToHouse(
            currHouse,
            curRes->getAllowedMovementDistance());
        pair<int, int> yRange = _city->getYRangeForAllowableDistanceToHouse(
            currHouse,
            curRes->getAllowedMovementDistance());
        //cout << "AAA_open_houses contains 849: " << (_open_houses.find(fiveNinetyNine) != 
        //        _open_houses.end()) << ".  ";
        for (int y=yRange.first; y<=yRange.second; ++y)
        {
            for (int x=xRange.first; x<=xRange.second; ++x)
            {
                for (const House* house : _open_houses_per_y_x[y][x])
                {  
                    if (house != currHouse)
                    {
                        vectorOpenHousesReduced.push_back(house);
                    }
                }
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
        unordered_set<const House*> previouslySelectedHousese{};
        previouslySelectedHousese.insert(currHouse);
        int maxTries = min(_max_num_of_tries_to_find_house, (int)vectorOpenHousesReduced.size());
        // TODO if max num of tries is 1/2 or greater than emptyHouses.size(), then use a set 
        // instead of a vector.
        //cout << "{maxtries, emptyHouses.size}: " << _max_num_of_tries_to_find_house << ", "
        //<< emptyHouses.size() << ";   "; 
        for (int ii=0; ii<maxTries; ++ii)
        {
            // choose a random house that has not been chosen before.
            const House* randHouse = selectRandom(vectorOpenHousesReduced); 
            // TODO check for nullptr, check for vector being size zero
            while ( (previouslySelectedHousese.find(randHouse) != previouslySelectedHousese.end()) ||
                    (_city->getDist(randHouse->getAddress(), currHouse->getAddress()) >
                        curRes->getAllowedMovementDistance())
                  )
            {
                previouslySelectedHousese.insert(randHouse);
                randHouse = selectRandom(vectorOpenHousesReduced);
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

// TODO if new house is not available, then don't move.
void Simulator_Basic_B::moveResidentIntoHouse (Resident* res, const House* newHouse)
{   
    //int res_per_house_sizeA = _res_per_house.size();
    //int house_per_resident_sizeA = _house_per_resident.size();
    //int open_houses_sizeA = _open_houses.size();
    if (_house_per_resident.find(res) != _house_per_resident.end())
    {   
        const House* oldHouse = _house_per_resident[res];

        _house_per_resident.erase(res);
        _res_per_house.erase(oldHouse);
        _open_houses.insert(oldHouse);
        Coordinate co = _city->getCoordinate(oldHouse->getAddress());
        _open_houses_per_y_x[co.getY()][co.getX()].insert(oldHouse);
    }

    _res_per_house.insert(pair<const House*, Resident*>(newHouse, res));

    _house_per_resident.insert(pair<Resident*, const House*>(res, newHouse));
    _open_houses.erase(newHouse);

    Coordinate co = _city->getCoordinate(newHouse->getAddress());

    if (_open_houses_per_y_x[co.getY()][co.getX()].find(newHouse) !=
         _open_houses_per_y_x[co.getY()][co.getX()].end())
    {
        _open_houses_per_y_x[co.getY()][co.getX()].erase(newHouse);
    }
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