#include "SimulationStarter.h"

#include <fstream>
#include <iostream>
#include "City_Grid.h"
#include "Color.h"

using namespace std;

SimulationComponents SimulationStarter::createSimulationComponents(string inputTextFile)
{
    SimulationComponents components;
    ifstream inputStream;
    inputStream.open(inputTextFile);
    if (inputStream.is_open())
    {
        string line = "";
        getline(inputStream, line);
        cout << "getline done" << endl;
        // city
        if (line.find("<city>") != string::npos)
        {   
            string cityType ="";
            getline(inputStream, line);
        
            if (line.find("<type>") != string::npos)
            {   
                getline(inputStream, cityType);
                getline(inputStream, line);
            }
            if (cityType.find("City_Grid") != string::npos)
            {   
                string width = "";
                getline(inputStream, line);
                if (line.find("<width>") != string::npos)
                {   
                    getline(inputStream, width);
                    getline(inputStream, line);
                }
                
                components.city = std::make_unique<City_Grid>(stoi(width));
            }
            getline(inputStream, line); // </city>
        }
        
        std::cout << "textfile city: " << components.city->getNumOfHouses() << endl;

        // base color per group

        getline(inputStream, line);
        if (line.find("base_color_per_group") != string::npos)
        {   auto aa = returnBaseColor(inputStream);
            auto bb = returnBaseColor(inputStream);
            cout << "aa: " << aa.first << ", " << aa.second << endl;
            cout << "bb: " << bb.first << ", " << bb.second << endl;
            //components.baseColorsPerGroupid.insert(returnBaseColor(inputStream));
            //components.baseColorsPerGroupid.insert(returnBaseColor(inputStream));
            //getline(inputStream, line); // </base_color_per_group>
            //cout << "line 56: " << components.baseColorsPerGroupid[1] << endl;
            //cout << "line 57: " << components.baseColorsPerGroupid[2] << endl;
        }

    }
    return components;
}

pair<int, BaseColor> SimulationStarter::returnBaseColor (ifstream& inputStream)
{
    string groupId = "";
    string baseColor = "";
    string line = "";
    getline(inputStream, line);
    if (line.find("group") != string::npos)
    {  
        getline(inputStream, line);
        if (line.find("group_id") != string::npos)
        {   
            getline(inputStream, groupId);
            getline(inputStream, line);
        }
        getline(inputStream, line);
        cout << "83 line: " << line << endl;
        if (line.find("base_color") != string::npos)
        {   
            getline(inputStream, baseColor);
            getline(inputStream, line);
        }
        getline(inputStream, line); // "</group>"
    }
    BaseColor c = _base_colors[leftTrim(baseColor)];
    return {stoi(groupId), c};
}

string SimulationStarter::leftTrim (string str)
{
    size_t start = str.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : str.substr(start);
}