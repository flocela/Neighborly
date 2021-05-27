#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <memory>

#include "CityFactory.h"
#include "CityFactory_Grid.h"
#include "CityMaker_CMDLine.h"
#include "CityFactory_Grid.h"
#include "ResidentsFactory_Flat.h"
#include "ResidentsFactory.h"
#include "ResidentsMaker_CMDLine.h"
#include "Printer_Graphic.h"
#include "Resident_Flat.h"

#include <thread>

std::vector<std::unique_ptr<CityFactory>> initCityFactories ();

std::vector<std::unique_ptr<ResidentsFactory>> initResidentFactories();

std::vector<CityFactory*> getCityFactoryPointers (
    std::vector<std::unique_ptr<CityFactory>>& cityFactories);

std::vector<ResidentsFactory*> getResidentFactoryPointers (
    std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories);

std::map<Coordinate, int> getHousePerCoordinate(const City& city);

int main() {

    std::vector<std::unique_ptr<CityFactory>> cityFactories;
    std::vector<std::unique_ptr<ResidentsFactory>> residentFactories;
    std::vector<CityFactory*> cityFactoryPointers;
    std::vector<ResidentsFactory*> residentFactoryPointers;

    cityFactories           = initCityFactories();
    residentFactories       = initResidentFactories();
    cityFactoryPointers     = getCityFactoryPointers(cityFactories);
    residentFactoryPointers = getResidentFactoryPointers(residentFactories);    

    CityMaker_CMDLine cityMaker{};
    std::unique_ptr<City> city = cityMaker.makeCity(cityFactoryPointers);
    std::map<Coordinate, int> housePerCoordinate = getHousePerCoordinate(*(city.get()));

    ResidentsMaker_CMDLine residentsMaker{};
    std::vector<std::unique_ptr<Resident>> residents = 
        residentsMaker.makeResidents(residentFactoryPointers, city->getSize());
    std::cout << "number of residents: " << residents.size();

    std::map<Color, int> intPerColor = {};
    std::map<int, Resident*> residentPerAddress = {};

    for (auto& resident : residents)
    {
        residentPerAddress[resident->getID()] = resident.get();
    }

    Printer_Graphic printer{640, 960, 20, 20};
    printer.printScreen();

    printer.print(residentPerAddress, housePerCoordinate, 1, 1, "Title");
    printer.keepScreen();
/*
    for (const auto& z : residentPerAddress)
    {
        delete z.second;
    }*/

    //Renderer renderer{640, 960, 20, 20};
    //renderer.RenderCity(colorPerCoordinateAnswer, colors);
    //SDL_Delay(5000);

  /*

  	Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  	Controller controller;
  	Game game(kGridWidth, kGridHeight);
  	game.Run(controller, renderer, kMsPerFrame);
  	std::cout << "Game has terminated successfully!\n";
  	std::cout << "Score: " << game.GetScore() << "\n";
  	std::cout << "Size: " << game.GetSize() << "\n";*/
  	return 0;
}

/*
constexpr std::size_t kFramesPerSecond{60};
  	constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  	constexpr std::size_t kScreenWidth{640};
  	constexpr std::size_t kScreenHeight{640};
  	constexpr std::size_t kGridWidth{32};
  	constexpr std::size_t kGridHeight{32};*/

std::vector<std::unique_ptr<CityFactory>> initCityFactories ()
{
    std::vector<std::unique_ptr<CityFactory>> cityFactories = {};
    cityFactories.emplace_back(std::make_unique<CityFactory_Grid>());
    return cityFactories;
}

std::vector<std::unique_ptr<ResidentsFactory>> initResidentFactories()
{
    std::vector<std::unique_ptr<ResidentsFactory>> residentFactories = {};
    residentFactories.emplace_back(std::make_unique<ResidentsFactory_Flat>());
    return residentFactories;
}

std::vector<CityFactory*> getCityFactoryPointers (
    std::vector<std::unique_ptr<CityFactory>>& cityFactories)
{
    std::vector<CityFactory*> cityFactoryPointers = {};
    for (auto& factory: cityFactories)
    {
        cityFactoryPointers.push_back(factory.get());
    }
     std::cout << "line 206 " << cityFactoryPointers[0]->toString() << std::endl;
    return cityFactoryPointers;
}

std::vector<ResidentsFactory*> getResidentFactoryPointers (
    std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories)
{
    std::vector<ResidentsFactory*> residentFactoryPointers = {};
    for (auto& factory : residentFactories)
    {
        residentFactoryPointers.push_back(factory.get());
    }
    return residentFactoryPointers;
}

std::map<Coordinate, int> getHousePerCoordinate(const City& city)
{
    std::map<Coordinate, int> housePerCoordinate = {};
    std::vector<int> addresses = city.getAddresses();
    for (int address : addresses)
    {
        housePerCoordinate[city.getCoordinate(address)] = address;
    }
    return housePerCoordinate;
}