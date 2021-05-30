#include "renderer.h"
#include <string>


#include <stdio.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

void renderText(SDL_Renderer *sdl_renderer)
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
                return;
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
                text = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
                if(!text) {
                    printf("Unable to create texture from rendered text!\n"
                           "SDL2 Error: %s\n", SDL_GetError());
                    return;
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
			
			// Initialize renderer color white for the background
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(sdl_renderer);

                // Set renderer color red to draw the square
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);

                // Draw filled square
                SDL_RenderFillRect(sdl_renderer, &squareRect);

                // Draw text
                SDL_RenderCopy(sdl_renderer, text, NULL, &textRect);

                // Update screen
                //SDL_RenderPresent(sdl_renderer);
}

Renderer::Renderer(
	const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width,
	const std::size_t grid_height
	):
	screen_width(screen_width),
    screen_height(screen_height),
    grid_width(grid_width),
    grid_height(grid_height) 
{
  	// Initialize SDL
  	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    	std::cerr << "SDL could not initialize.\n";
    	std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
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

  	sdl_window = SDL_CreateWindow(
        "Snake Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		screen_width,
        screen_height, 
		SDL_WINDOW_SHOWN
	);

  	if (nullptr == sdl_window) {
    	std::cerr << "Window could not be created.\n";
    	std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  	}
	else
	{
		// Create renderer
  		sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  		if (nullptr == sdl_renderer) {
    		std::cerr << "Renderer could not be created.\n";
    		std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
		}
		else
		{

			/*
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
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(sdl_renderer);

                // Set renderer color red to draw the square
                SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);

                // Draw filled square
                SDL_RenderFillRect(sdl_renderer, &squareRect);

                // Draw text
                SDL_RenderCopy(sdl_renderer, text, NULL, &textRect);

                // Update screen
                SDL_RenderPresent(sdl_renderer);
            }
			*/

            // Destroy renderer
           // SDL_DestroyRenderer(sdl_renderer); TODO Destroy Renderer

		}
	}
	
}

void Renderer::poll()
{
    SDL_Event e;
    int counter = 0;
    while (SDL_WaitEvent(&e) != 0)
    {   
        counter ++;
        if (e.type == SDL_QUIT)
        {
            //_keep_polling = false;
            break;
        }
    }
}

Renderer::~Renderer() {
  	SDL_DestroyWindow(sdl_window);
  	SDL_Quit();
}

std::map<Color, ColorInfo> getColorInfo ()
{
    std::map<Color, ColorInfo> colorMap = {};
    for (ColorInfo colorInfo : _the_colors)
    {
        colorMap[colorInfo._my_color] = colorInfo;
    }
    return colorMap;
}

void Renderer::RenderCity (
  	std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
  	Coordinate placement
)
{
	renderText(sdl_renderer);

    std::map<Color, ColorInfo> colorMap = getColorInfo();
    int grid_width = 20;
    int grid_height = 20;
    SDL_Rect block;
    block.w = 12;
    block.h = 12;
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    //SDL_RenderClear(sdl_renderer);

    for (auto const& x : coordinatesPerColor)
    {
        Color currColor = x.first;
        std::vector<Coordinate> coordinates = x.second;

        ColorInfo colorInfo = colorMap[currColor];
        std::vector<int> rgba = colorInfo.rgba;

        SDL_SetRenderDrawColor(sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
        for (Coordinate c : coordinates)
        {
            block.x = placement.getX() + c.getX() * grid_width + 4;
            block.y = placement.getY() + c.getY() * grid_height + 4;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render()
{
  	// TODO is this function ever called?
    //SDL_Rect block;
    //block.w = 50;
    //block.h = 50;

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);

    SDL_RenderPresent(sdl_renderer);
}



void Renderer::UpdateWindowTitle(int score, int fps) {
  	std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  	SDL_SetWindowTitle(sdl_window, title.c_str());
}


