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

        // Account for spacing between letters and line height
        textRect.w = 0.5 * fontSize * textString.length();
        textRect.h = 1.75 * fontSize; // This is the same 1.75 that is in the AxisFormat to find the height
        // of the text from the fontSize.
        
        SDL_FreeSurface(textSurface);
    }
    if (centered == 1) // centered horizontally
    {
        textRect.x = x - textRect.w/2;
        textRect.y = y - textRect.h;
    }
    else if (centered == 2)
    {
        textRect.x = x - 1.5 * textRect.w;
        textRect.y = y - 0.5 * textRect.h;
    }
    else if (centered == 3)
    {
        textRect.x = x - textRect.w/2;
        textRect.y = y;
    }
    else if (centered == 4)
    {
        textRect.x = x;
        textRect.y = y;
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

void Renderer::addBlocksByColor(
	int width,
	int height,
	std::vector<Coordinate> coordinates,
	std::vector<int> rgba
)
{
    SDL_Rect block;
    block.w = width;
    block.h = height;

    SDL_SetRenderDrawColor(sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    for (Coordinate c : coordinates)
    {
        block.x = c.getX();
        block.y = c.getY();
        SDL_RenderFillRect(sdl_renderer, &block);
    }

}

void Renderer::addBlock (
	int width, 
	int height,
	Coordinate coordinate,
	std::vector<int> rgba
	)
{
    SDL_Rect block;
    block.w = width;
    block.h = height;
    SDL_SetRenderDrawColor(sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    block.x = coordinate.getX();
    block.y = coordinate.getY();
    SDL_RenderFillRect(sdl_renderer, &block);
}

void Renderer::fillBlocks (std::vector<SDL_Rect> blocks)
{
    for (SDL_Rect block : blocks)
    {
        fillBlock(block);
    }
}

void Renderer::renderTexts (std::vector<TextRect> texts)
{
    for (TextRect tr : texts)
    {
       renderText(tr.xPixel, tr.yPixel, tr.text, tr.position);
    }
}
