/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
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

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

int oldCodeFromAminoshbh(int argc, char* argv[])
{
// Unused argc, argv
    (void) argc;
    (void) argv;

    // Initialize SDL2
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL2 could not be initialized!\n"
               "SDL2 Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL2_ttf
    TTF_Init();

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("SDL2_ttf sample",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            printf("Renderer could not be created!\n"
                   "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Declare rect of square
            SDL_Rect squareRect;

            // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
            squareRect.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
            squareRect.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;

            // Square position: In the middle of the screen
            squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
            squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;

            TTF_Font *font = TTF_OpenFont(FONT_PATH, 40);
            if(!font) {
                printf("Unable to load font: '%s'!\n"
                       "SDL2_ttf Error: %s\n", FONT_PATH, TTF_GetError());
                return 0;
            }

            SDL_Color textColor           = { 0x00, 0x00, 0x00, 0xFF };
            SDL_Color textBackgroundColor = { 0xFF, 0xFF, 0xFF, 0xFF };
            SDL_Texture *text = NULL;
            SDL_Rect textRect;

            SDL_Surface *textSurface = TTF_RenderText_Shaded(font, "Red square", textColor, textBackgroundColor);
            if(!textSurface) {
                printf("Unable to render text surface!\n"
                       "SDL2_ttf Error: %s\n", TTF_GetError());
            } else {
                // Create texture from surface pixels
                text = SDL_CreateTextureFromSurface(renderer, textSurface);
                if(!text) {
                    printf("Unable to create texture from rendered text!\n"
                           "SDL2 Error: %s\n", SDL_GetError());
                    return 0;
                }

                // Get text dimensions
                textRect.w = textSurface->w;
                textRect.h = textSurface->h;

                SDL_FreeSurface(textSurface);
            }

            textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
            textRect.y = squareRect.y - textRect.h - 10;
            std::cout << "textRect.x = " << textRect.x;
            std::cout << "textRect.y = " << textRect.y;
            textRect.x = 500;
            textRect.y = 500;
            
            // Event loop exit flag
            bool quit = false;

            // Event loop
            while(!quit)
            {
                SDL_Event e;

                // Wait indefinitely for the next available event
                SDL_WaitEvent(&e);

                // User requests quit
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }

                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(renderer);

                // Set renderer color red to draw the square
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

                // Draw filled square
                SDL_RenderFillRect(renderer, &squareRect);

                // Draw text
                SDL_RenderCopy(renderer, text, NULL, &textRect);

                // Update screen
                SDL_RenderPresent(renderer);
            }

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL2_ttf
    TTF_Quit();

    // Quit SDL
    SDL_Quit();

    return 0;
}

std::vector<std::unique_ptr<CityFactory>> initCityFactories ();

std::vector<std::unique_ptr<ResidentsFactory>> initResidentFactories();

std::vector<CityFactory*> fromCityFactoriesGetPointers (
    std::vector<std::unique_ptr<CityFactory>>& cityFactories);

std::vector<ResidentsFactory*> fromResidentFactoriesGetPointers (
    std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories);

std::map<Coordinate, int> getHousePerCoordinate(const City& city);

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    std::vector<std::unique_ptr<CityFactory>> cityFactories =
        initCityFactories();
    std::vector<std::unique_ptr<ResidentsFactory>> residentFactories =
        initResidentFactories();
    std::vector<CityFactory*> cityFactoryPointers =
        fromCityFactoriesGetPointers(cityFactories);
    std::vector<ResidentsFactory*> residentFactoryPointers =
        fromResidentFactoriesGetPointers(residentFactories);; 

    CityMaker_CMDLine cityMaker{};
    //std::unique_ptr<City> city = cityMaker.makeCity(cityFactoryPointers);
    std::unique_ptr<City> city = cityMaker.makeBaseCity(cityFactoryPointers);
    std::map<Coordinate, int> housePerCoordinate = getHousePerCoordinate(*(city.get()));

    ResidentsMaker_CMDLine residentsMaker{};
    //std::vector<std::unique_ptr<Resident>> residents = 
    //    residentsMaker.makeResidents(residentFactoryPointers, city->getSize());
    std::vector<std::unique_ptr<Resident>> residents = 
        residentsMaker.makeBaseResidents(residentFactoryPointers, city->getSize());
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
    return 0; 
}

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

std::vector<CityFactory*> fromCityFactoriesGetPointers (
    std::vector<std::unique_ptr<CityFactory>>& cityFactories)
{
    std::vector<CityFactory*> cityFactoryPointers = {};
    for (auto& factory: cityFactories)
    {
        cityFactoryPointers.push_back(factory.get());
    }
    return cityFactoryPointers;
}

std::vector<ResidentsFactory*> fromResidentFactoriesGetPointers (
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