#include "renderer.h"
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <SDL.h>
#include <SDL_ttf.h>


// Define screen dimensions
#define FONT_PATH   "assets/pacifico/Pacifico.ttf"


void Renderer::renderText (
    int x, 
    int y, 
    int fontSize,
	char* textString,
	SDL_Color textColor,
	SDL_Color backgroundColor
)
{
    TTF_Font *font = TTF_OpenFont(FONT_PATH, fontSize);
    if(!font) {
        printf(
			"Unable to load font: '%s'!\n"
            "SDL2_ttf Error: %s\n", FONT_PATH, TTF_GetError()
			);
        return;
    }

    SDL_Texture *text = NULL;
    SDL_Rect textRect;

    SDL_Surface *textSurface = TTF_RenderText_Shaded(
        font, 
        textString,
        textColor,
        backgroundColor
    );
    if(!textSurface) {
        printf(
			"Unable to render text surface!\n"
            "SDL2_ttf Error: %s\n", TTF_GetError()
		);
    } 
	else 
	{
        // Create texture from surface pixels
        text = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
        if(!text) {
            printf(
				"Unable to create texture from rendered text!\n"
                "SDL2 Error: %s\n", SDL_GetError()
			);
            return;
        }

        // Get text dimensions
        textRect.w = strlen(textString) * 6;
        textRect.h = 20;

        SDL_FreeSurface(textSurface);
    }
    textRect.x = x;
    textRect.y = y;
			
	// Initialize renderer color white for the background
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Clear screen
    //SDL_RenderClear(sdl_renderer);

    // Set renderer color red to draw the square
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);

    // Draw text
    SDL_RenderCopy(sdl_renderer, text, NULL, &textRect);
}

Renderer::Renderer(
	const std::size_t screen_width,
    const std::size_t screen_height):
	screen_width(screen_width),
    screen_height(screen_height)
{
  	if (!initVideo())
      return;
    
    TTF_Init();
    
    if (!linuxSettings())
        return;
        
    if (!initWindow())
        return;
        
    initRenderer();
	
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

void Renderer::AddCity (
  	std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
  	Coordinate placement,
    int gridSize,
    int blockSize,
    int minX,
	int maxX,
	int minY,
	int maxY 
)
{
    std::map<Color, ColorInfo> colorMap = getColorInfo();

    addCityXAxes(placement, gridSize, blockSize, minX, maxX);
    addCityYAxes(placement, gridSize, blockSize, minY, maxY);

    SDL_Rect block;
    block.w = blockSize;
    block.h = blockSize;
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);

    for (auto const& x : coordinatesPerColor)
    {
        Color currColor = x.first;
        std::vector<Coordinate> coordinates = x.second;

        ColorInfo colorInfo = colorMap[currColor];
        std::vector<int> rgba = colorInfo.rgba;

        SDL_SetRenderDrawColor(sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
        for (Coordinate c : coordinates)
        {
            block.x = placement.getX() - block.w/2 + c.getX() * gridSize;
            block.y = placement.getY() - block.w/2 + c.getY() * gridSize;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

    

}

void Renderer::addCityXAxes(
    Coordinate placement,
    int gridSize, 
    int blockSize,
    int minX,
	int maxX
)
{
    SDL_SetRenderDrawColor(sdl_renderer, 200, 200, 200, 200);
    SDL_Rect block;

    // axis line
    block.w = (maxX - minX) * gridSize + 4 * gridSize;
    block.h = 1;
    block.x = placement.getX() - 2 * gridSize;
    block.y = placement.getY() - 2 * gridSize;
    SDL_RenderFillRect(sdl_renderer, &block);

    // axis ticks
    int flooredTen = minX - ( minX % 10 );
    int nextTen    = flooredTen + 10;
    int nextTenMinusMinX = nextTen - minX;
    int numOfDashes = (maxX - minX)/10 + 2;

    block.w = blockSize;
    block.h = gridSize;
    block.x = placement.getX() - block.w/2;
    block.y = placement.getY() - 2 * gridSize;
    SDL_RenderFillRect(sdl_renderer, &block);

    for (int ii=0; ii<numOfDashes; ii++)
    {
        block.x = placement.getX() - block.w/2 + (nextTenMinusMinX * gridSize) + (ii * 10 * gridSize);
        block.y = placement.getY() - 2 * gridSize;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // axis title
    char q[] = "X Axis";

    renderText(
        placement.getX() + ( (maxX - minX) * gridSize + 4 * gridSize ) /2,
        placement.getY() - 2 * gridSize,
        14, 
        q, 
        {0x00, 0x00, 0x00, 0x00}, 
        {0xFF, 0xFF, 0xFF, 0xFF}
    );
}

void Renderer::addCityYAxes(
    Coordinate placement,
    int gridSize, 
    int blockSize,
	int minY,
	int maxY
)
{
    SDL_SetRenderDrawColor(sdl_renderer, 200, 200, 200, 200);
    SDL_Rect block;

    // axis line
    block.w = 1;
    block.h = (maxY - minY) * gridSize + 4 * gridSize;
    block.x = placement.getX() - 2 * gridSize;
    block.y = placement.getY() - 2 * gridSize;
    SDL_RenderFillRect(sdl_renderer, &block);

    // axis ticks
    int flooredTen = minY - ( minY % 10 );
    int nextTen    = flooredTen + 10;
    int nextTenMinusMinY = nextTen - minY;
    int numOfDashes = (maxY - minY)/10 + 1;

    block.w = gridSize;
    block.h = blockSize;
    block.x = placement.getX() - 2 * gridSize;
    block.y = placement.getY() - block.h/2;
    SDL_RenderFillRect(sdl_renderer, &block);

    for (int ii=0; ii<numOfDashes; ii++)
    {
        block.x = placement.getX() - 2 * gridSize;
        block.y = placement.getY() - block.h/2 + (nextTenMinusMinY * gridSize) + (ii * 10 * gridSize);
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}

void Renderer::startFrame()
{
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);
}

void Renderer::endFrame()
{
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  	std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  	SDL_SetWindowTitle(sdl_window, title.c_str());
}

bool Renderer::initVideo()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    	std::cerr << "SDL could not initialize.\n";
    	std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
  	}
    return true;
}

bool Renderer::linuxSettings()
{
	#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    	// Disable compositor bypass
    	if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    	{
    	    std::cerr << "SDL can not disable compositor bypass!\n";
    	    return false;
   	 	}
  	#endif
    return true;
}

bool Renderer::initWindow()
{
    sdl_window = SDL_CreateWindow(
        "Neighbors", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		screen_width,
        screen_height, 
		SDL_WINDOW_SHOWN
	);
    if (nullptr == sdl_window) {
    	std::cerr << "Window could not be created.\n";
    	std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
        return false;
  	}
    return true;
}

bool Renderer::initRenderer()
{
    sdl_renderer = SDL_CreateRenderer(
        sdl_window, 
        -1, 
        SDL_RENDERER_ACCELERATED
        );
  	if (nullptr == sdl_renderer) {
    	std::cerr << "Renderer could not be created.\n";
    	std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
	}
    return true;
}

void Renderer::setMinMaxCityCoordinates(std::vector<Coordinate> coordinates)
{
    (void) coordinates;
}
