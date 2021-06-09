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

		// Uses rgba values from _the_colors global variable
  		void AddTopLeftDotGraph (
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
			Coordinate orig, // Top left most point on graph. Allow room for titles.
			int gridSize,
			int blockSize,
			int minX,
			int maxX,
			int minY,
			int maxY,
			std::string title
		);
  		void startFrame();
		void endFrame();
  		void UpdateWindowTitle(int score, int fps);
		
 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;

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

		void renderText (
			int x, 
			int y, 
			int fontSize,
			char* text,
			SDL_Color textColor,
			SDL_Color backgroundColor);
		bool initVideo ();
		bool linuxSettings ();
		bool initWindow ();
		bool initRenderer ();
		void setMinMaxCityCoordinates (std::vector<Coordinate> coordinates);
		std::vector<Coordinate> extractCoordinates (
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor
		);
		void addCityXAxes(
			Coordinate placement,
			int fontsize,
			int gridSize, 
			int blockSize,
			int minX, 
			int maxX
		);
		void addCityYAxes(
			Coordinate placement,
			int gridSize, 
			int blockSize, 
			int minY, 
			int maxY
		);
		void addCityHouses(
    		Coordinate cityOrigin,
			int gridSize,
			int blockSize,
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
			std::map<Color, ColorInfo> colorMap
		);

		void addTitle (
			Coordinate placement,
			char* title,
			int fontsize
		);
};

#endif