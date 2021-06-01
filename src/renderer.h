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
			const std::size_t screen_height,
           	const std::size_t grid_width, 
			const std::size_t grid_height);
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

 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;
  		const std::size_t grid_width;
  		const std::size_t grid_height;

		
		void renderText (int x, int y, int fontSize);
		bool initVideo ();
		bool linuxSettings ();
		bool initWindow ();
		bool initRenderer ();
		void setMinMaxCityCoordinates (std::vector<Coordinate> coordinates);
		std::vector<Coordinate> extractCoordinates (
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor
		);
};

#endif