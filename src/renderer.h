#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "Coordinate.h"
#include <map>
#include "TextRect.h"
#include <utility>
#include "Color.h"

class Renderer {
 	public:
  		Renderer(
			const std::size_t screen_width, 
			const std::size_t screen_height);
  		~Renderer();
		  
  		void startFrame();
		void endFrame();
  		void UpdateWindowTitle(int score, int fps);

		void setColorToMedGrey();
		void setColorToBlack();
		void setColorToRed();

		void fillBlock (SDL_Rect block);
		void fillBlocks (std::vector<SDL_Rect> blocks);

		void renderText (
			int x, 
			int y,
			std::string text,
			int centered
		);

		void renderTexts (std::vector<TextRect> texts);

		void setTextFormats (
			SDL_Color textColor,
			SDL_Color textBackgroundColor,
			int fontSize
		);

		// @coordinates: the coordinates are in pixels, not in city coordinates.
		// They refer to the top left point on the block.
		void addBlocksByColor(
			int width,
			int height,
			std::vector<Coordinate> coordinates,
			std::vector<int> rgba
		);

		void addBlock (
			int width, 
			int height,
			Coordinate coordinate,
			std::vector<int> rgba
		);
		
 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;

		SDL_Color _text_color;
		SDL_Color _text_background_color;
		int _font_height;

		bool initVideo ();
		bool linuxSettings ();
		bool initWindow ();
		bool initRenderer ();

		void renderText (
			int x, 
			int y, 
			int fontSize,
			std::string text,
			SDL_Color textColor,
			SDL_Color backgroundColor,
			int centered
		);

};

#endif