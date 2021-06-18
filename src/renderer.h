#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "Coordinate.h"
#include <map>
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

		void fillBlock(SDL_Rect block);

		void renderText (
			int x, 
			int y,
			std::string text,
			int centered
		);

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
		
 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;

		SDL_Color _text_color;
		SDL_Color _text_background_color;
		int _font_size;

		// chart title is vertically offset from the origin by _title_offset
		// from the x-axis by x-title-offset
		const int _title_offset = 10;
		
		// x-axis numbers are vertically offset from origin by x_num_offset * gridSize
		const int x_num_offset = 10;

		// x-axis is vertically offset from origin by x-axis-offset
		const int x_axis_offset = 50;

		// x-tick marks sit above the x axis and are vertically offset
		// from the x-axis by x-tick-offset
		const int x_tick_offset = 6;

		// x-axis title sits above the x-axis and are vertically offset
		// from the x-axis by x-title-offset
		const int x_title_offset = 30;

		// x-axis overruns its data by x_axis_overrun
		const int x_axis_overrun = 20;

		bool initVideo ();
		bool linuxSettings ();
		bool initWindow ();
		bool initRenderer ();
		void setMinMaxCityCoordinates (std::vector<Coordinate> coordinates);
		std::vector<Coordinate> extractCoordinates (
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor
		);

		void addTitle (
			Coordinate placement,
			char* title,
			int fontsize
		);

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