#include "Renderer.h"

#include <cstring>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>

using namespace std;

#define FONT_PATH   "assets/pacifico/Pacifico.ttf"

Renderer::Renderer (
    const size_t screen_width,
    const size_t screen_height,
    string title
): _screen_width(screen_width),
   _screen_height(screen_height)
{
  	if (!initVideo())
      return;
    
    TTF_Init();
    
    if (!linuxSettings())
        return;
        
    if (!initWindow(title))
        return;
        
    initRenderer();
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(_sdl_renderer);
  	SDL_DestroyWindow(_sdl_window);
    TTF_Quit();
  	SDL_Quit();
}

void Renderer::startFrame()
{
    SDL_SetRenderDrawColor(_sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(_sdl_renderer);
}

void Renderer::endFrame()
{
    SDL_RenderPresent(_sdl_renderer);
}

void Renderer::fillBlock(Rect block, vector<uint8_t> rgba)
{
    SDL_Rect rect = {block._x__px, block._y__px, block.width, block.height};
    SDL_SetRenderDrawColor(_sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    SDL_RenderFillRect(_sdl_renderer, &rect);
}

void Renderer::fillBlocks (vector<Rect> blocks, vector<uint8_t> rgba)
{

    SDL_SetRenderDrawColor(_sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    for (Rect block : blocks)
    {   SDL_Rect rect = {block._x__px, block._y__px, block.width, block.height};
        SDL_RenderFillRect(_sdl_renderer, &rect);
    }
}

void Renderer::fillBlock (
	int width, 
	int height,
	Coordinate coordinate,
	vector<uint8_t> rgba
)
{
    SDL_Rect block;
    block.w = width;
    block.h = height;
    block.x = coordinate.getX();
    block.y = coordinate.getY();

    SDL_SetRenderDrawColor(_sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    SDL_RenderFillRect(_sdl_renderer, &block);
}

void Renderer::fillBlocks(
	int width,
	int height,
	vector<Coordinate> coordinates,
	vector<uint8_t> rgba
)
{
    SDL_Rect block;
    block.w = width;
    block.h = height;

    SDL_SetRenderDrawColor(_sdl_renderer, rgba[0], rgba[1], rgba[2], rgba[3]);

    for (Coordinate c : coordinates)
    {
        block.x = c.getX();
        block.y = c.getY();
        SDL_RenderFillRect(_sdl_renderer, &block);
    }
}

void Renderer::renderText (
    int x, 
    int y,
    string textString,
    int letterHeight,
    double widthMultiplier,
	std::vector<uint8_t> rgbaText,
	std::vector<uint8_t> rgbaBackground,
    int position
)
{
    if (textString.size() == 0)
    {
        return;
    }
    
    TTF_Font *font = TTF_OpenFont(FONT_PATH, 100);

    if(!font) 
    {
        printf("Unable to load font: '%s'!\n SDL2_ttf Error: %s\n", FONT_PATH, TTF_GetError());
        return;
    }

    SDL_Texture *text = NULL;
    SDL_Rect sdlRect;

    SDL_Color textColor = {rgbaText[0], rgbaText[1], rgbaText[2], rgbaText[3]};
    SDL_Color backgroundColor = {
        rgbaBackground[0], 
        rgbaBackground[1],
        rgbaBackground[2],
        rgbaBackground[3]
    };
    SDL_Surface *textSurface = TTF_RenderText_Shaded(
        font, 
        &textString[0],
        textColor,
        backgroundColor
    );

    if(!textSurface)
    {
        printf("Unable to render text surface!\n SDL2_ttf Error: %s\n", TTF_GetError());
        return;
    } 
	
    // create texture from surface pixels
    text = SDL_CreateTextureFromSurface(_sdl_renderer, textSurface);
    if(!text)
    {
        printf(
            "Unable to create texture from rendered text!\n SDL2 Error: %s\n", SDL_GetError());
        return;
    }

    // account for spacing between letters and line height
    sdlRect.w = widthMultiplier * letterHeight * textString.length();
    sdlRect.h = letterHeight; 
    
    SDL_FreeSurface(textSurface);
    
    if (position == 1)
    {
        sdlRect.x = x - sdlRect.w/2;
        sdlRect.y = y;
    }
    else if (position == 2)
    {
        sdlRect.x = x;
        sdlRect.y = y - 0.5 * sdlRect.h - 2;
    }
    else if (position == 3)
    {
        sdlRect.x = x - sdlRect.w;
        sdlRect.y = y - 0.5 * sdlRect.h -2;
    }
    else if (position == 4)
    {
        sdlRect.x = x;
        sdlRect.y = y;
    }
    else if (position == 5)
    {
        sdlRect.x = x - sdlRect.w/2;
        sdlRect.y = y - sdlRect.h;
    }
    
    // draw text
    SDL_RenderCopy(_sdl_renderer, text, NULL, &sdlRect);
}

void Renderer::renderTexts (vector<TextRect> texts)
{
    for (TextRect tr : texts)
    {
       renderText(
           tr._x_px, 
           tr._y_px, 
           tr._text,
           tr._letter_height,
           tr._width_multiplier,
           tr._text_color,
           tr._text_background_color,
           tr._position
           );
    }
}

bool Renderer::initVideo()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    	cerr << "SDL could not initialize.\n";
    	cerr << "SDL_Error: " << SDL_GetError() << "\n";
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
    	    cerr << "SDL can not disable compositor bypass!\n";
    	    return false;
   	 	}
  	#endif
    return true;
}

bool Renderer::initWindow(string title)
{
    _sdl_window = SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
		_screen_width,
        _screen_height, 
		SDL_WINDOW_SHOWN
	);
    if (nullptr == _sdl_window) {
    	cerr << "Window could not be created.\n";
    	cerr << " SDL_Error: " << SDL_GetError() << "\n";
        return false;
  	}
    return true;
}

bool Renderer::initRenderer()
{
    _sdl_renderer = SDL_CreateRenderer(
        _sdl_window, 
        -1, 
        SDL_RENDERER_ACCELERATED
        );
  	if (nullptr == _sdl_renderer) {
    	cerr << "Renderer could not be created.\n";
    	cerr << "SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }
    return true;
}