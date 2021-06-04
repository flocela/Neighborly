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
  		void AddCity (
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
			Coordinate placement,
			int gridSize,
			int blockSize,
			int minX,
			int maxX,
			int minY,
			int maxY
		);
  		void startFrame();
		void endFrame();
  		void UpdateWindowTitle(int score, int fps);
		void setGridWidthAndHeight (int width, int height);
		
 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;
  		std::size_t grid_width;
  		std::size_t grid_height;

		
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
};

#endif