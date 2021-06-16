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
	std::string textString,
	SDL_Color textColor,
	SDL_Color backgroundColor,
    int centered
)
{
    if (centered == 2)
    {
        std::cout <<"renderer line 27 x: " << x << std::endl;
    }
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
        &textString[0],
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
        textRect.w = textString.length() * 6;
        textRect.h = 2 * fontSize;

        SDL_FreeSurface(textSurface);
    }
    if (centered == 1)
    {
        textRect.x = x - textRect.w/2;
        textRect.y = y - textRect.h;
    }
    else if (centered == 2)
    {
        textRect.x = x - 1.5 * textRect.w;
        textRect.y = y - 0.6 * textRect.h;
    }
    
    // Draw text
    SDL_RenderCopy(sdl_renderer, text, NULL, &textRect);
}

void Renderer::renderText (
    int x, 
    int y,
    std::string text,
    int centered
)
{
    renderText(
        x,
        y,
        _font_size,
        text,
        _text_color,
        _text_background_color,
        centered
    );
}

void Renderer::renderNumbersHorizontally (
    int x, 
	int y,
	int firstNum,
	int diff, // differentece between numbers
	int spacing, // pixel distance between numbers
	int repeated, // number of numbers
	int centered
)
{
    renderNumbersHorizontally(
        x,
        y,
        _font_size,
        firstNum,
        diff,
        spacing,
        repeated,
        _text_color,
        _text_background_color,
        centered
    );
}
void Renderer::renderNumbersHorizontally (
    int x, 
	int y,
	int fontSize,
	int firstNum,
	int diff, // difference between numbers
	int spacing, // pixel distance between numbers
    int repeated, // number of numbers
	SDL_Color textColor,
	SDL_Color backgroundColor,
	int centered
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
    std::cout << "renderer: repeated: " << repeated << std::endl;
    for (int ii=0 ; ii<repeated; ++ii)
    {
        std::string numString = std::to_string(firstNum + diff * ii);
        SDL_Surface *textSurface = TTF_RenderText_Shaded(
        font, 
        &numString[0],
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
        textRect.w = numString.length() * 8 + numString.length();
        textRect.h = 1.75 * fontSize;

        SDL_FreeSurface(textSurface);
        }
        if (centered == 1)
        {
            textRect.x = x + spacing * ii - textRect.w/2;
            textRect.y = y - textRect.h;
        }
        else if (centered == 2)
        {
            textRect.x = x - textRect.w/2;
            textRect.y = y;
        }
        SDL_RenderCopy(sdl_renderer, text, NULL, &textRect);
        }

    
}

void Renderer::setTextFormats (
    SDL_Color textColor,
    SDL_Color textBackgroundColor,
    int fontSize
)
{
    _text_color = textColor;
    _text_background_color = textBackgroundColor;
    _font_size = fontSize;
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
    SDL_DestroyRenderer(sdl_renderer);
  	SDL_DestroyWindow(sdl_window);
    TTF_Quit();
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

void Renderer::AddTopLeftDotGraph (
  	std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
  	Coordinate orig,
    int gridSize,
    int blockSize,
    int minX,
	int maxX,
	int minY,
	int maxY,
    std::string title 
)
{
    (void) title;
    (void) coordinatesPerColor;
    std::map<Color, ColorInfo> colorMap = getColorInfo();

    //int xAxesLength = (maxX - minX) * gridSize + x_axis_overrun;
    
    Coordinate xAxes = Coordinate{orig.getX(), orig.getY() + x_axis_offset};
    Coordinate yAxes = Coordinate{orig.getX(), orig.getY() + 10 * gridSize};
    //Coordinate cAxes = Coordinate{orig.getX(), orig.getY() +  9 * gridSize};
    
    Coordinate titleCoord = Coordinate{
        orig.getX() + ((maxX - minX)/2) * gridSize, 
        orig.getY() + _title_offset };
    char* title_arr = &title[0];
    addTitle (titleCoord, title_arr, 20);
    addCityXAxes(xAxes, 14, gridSize, blockSize, minX, maxX);
    addCityYAxes(yAxes, gridSize, blockSize, minY, maxY);

    
    //addCityHouses(cAxes, gridSize, blockSize, coordinatesPerColor, colorMap);
    
}

void Renderer::addTitle (
    Coordinate placement,
    char* title,
    int fontsize
)
{
    (void) title;
    renderText(
        placement.getX(),
        placement.getY(),
        fontsize, 
        "title",
        {100, 100, 100, 100}, 
        {0xFF, 0xFF, 0xFF, 0xFF},
        1
    );
}

void Renderer::setColorToMedGrey ()
{
    SDL_SetRenderDrawColor(sdl_renderer, 200, 200, 200, 200);
}

void Renderer::setColorToBlack ()
{
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0xFF);
}

void Renderer::setColorToRed ()
{
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0, 0, 0xFF);
}

void Renderer::fillBlock(SDL_Rect block)
{
    SDL_RenderFillRect(sdl_renderer, &block);
}
void Renderer::addCityXAxes(
    Coordinate placement,
    int fontsize,
    int gridSize, 
    int blockSize,
    int minX,
	int maxX
)
{
    SDL_SetRenderDrawColor(sdl_renderer, 200, 200, 200, 200);
    SDL_Rect block;

    // horizontal axis.
    block.w = (maxX - minX) * gridSize + x_axis_overrun;
    block.h = 1;
    block.x = placement.getX();
    block.y = placement.getY();
    SDL_RenderFillRect(sdl_renderer, &block);

    // axis ticks
    int flooredTen = minX - ( minX % 10 );
    int nextTen    = flooredTen + 10;
    int nextTenMinusMinX = nextTen - minX;
    int numOfDashes = (maxX - minX)/10 + 1;

    block.w = blockSize;
    block.h = gridSize;
    block.x = placement.getX() - block.w/2;
    block.y = placement.getY() - x_tick_offset;
    SDL_RenderFillRect(sdl_renderer, &block);

    for (int ii=0; ii<numOfDashes; ii++)
    {
        block.x = placement.getX() - block.w/2 + (nextTenMinusMinX * gridSize) + (ii * 10 * gridSize);
        block.y = placement.getY()- x_tick_offset;
        SDL_RenderFillRect(sdl_renderer, &block);
    }


    renderText(
        placement.getX() + ((maxX - minX) * gridSize) - (20 * gridSize),
        placement.getY() - x_title_offset,
        fontsize, 
        "x axis",
        {100, 100, 100, 100}, 
        {0xFF, 0xFF, 0xFF, 0xFF},
        1
    );
}

void Renderer::renderBlocksHorizontally (
    SDL_Rect firstBlock,
    int pixelsBetweenBlocks,
    int numOfBlocks
)
{
    SDL_Rect current;
    current.w = firstBlock.w;
    current.h = firstBlock.h;
    current.x = firstBlock.x;
    current.y = firstBlock.y;

    for (int ii=0; ii<numOfBlocks; ++ii)
    {
        current.x = firstBlock.x + ii * pixelsBetweenBlocks;
        SDL_RenderFillRect(sdl_renderer, &current);
    }
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
    block.x = placement.getX();
    block.y = placement.getY();
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
    _text_color =  {100, 100, 100, 100};
    _text_background_color = {0xFF, 0xFF, 0xFF, 0xFF};
    _font_size = 18;
    return true;
}

void Renderer::setMinMaxCityCoordinates(std::vector<Coordinate> coordinates)
{
    (void) coordinates;
}

void Renderer::addCityHouses(
    Coordinate cityOrigin,
	int gridSize,
	int blockSize,
	std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
    std::map<Color, ColorInfo> colorMap
)
{
    SDL_Rect block;
    block.w = blockSize;
    block.h = blockSize;

    for (auto const& x : coordinatesPerColor)
    {
        Color currColor = x.first;
        std::vector<Coordinate> coordinates = x.second;

        ColorInfo colorInfo = colorMap[currColor];
        std::vector<int> rgba = colorInfo.rgba;

        SDL_SetRenderDrawColor(sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
        for (Coordinate c : coordinates)
        {
            block.x = cityOrigin.getX() - block.w/2 + c.getX() * gridSize;
            block.y = cityOrigin.getY() - block.w/2 + c.getY() * gridSize;
            SDL_RenderFillRect(sdl_renderer, &block);
        }
    }

}
