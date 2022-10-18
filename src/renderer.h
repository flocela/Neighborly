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
			std::string textString,
			int letterHeight,
			double widthMultiplier,
			SDL_Color textColor,
			SDL_Color textBackgroundColor,
			int position
		);

		void renderText (
			int x, 
			int y,
			std::string textString,
			int letterHeight,
			double widthMultiplier,
			int position
		);

		void renderTexts (std::vector<TextRect> texts);

		void renderTexts (
			std::vector<TextRect> texts,
			SDL_Color textColor,
			SDL_Color textBackgroundColor
		);

		// TODO remove, I set text formats when priting text
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

		void setWidthMultiplier (double multiplier) {_width_multiplier = multiplier;};
		double widthMultiplier() { return _width_multiplier; }
		
 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;


		SDL_Color _text_color = {100, 100, 100, 100};
		SDL_Color _text_background_color = {0xAA, 0xFF, 0xFF, 0xFF};
		int _font_height;
		double _width_multiplier = 0.3; // TODO is passed in with every render text, shoudl be deleted.

		bool initVideo ();
		bool linuxSettings ();
		bool initWindow ();
		bool initRenderer ();

};

#endif