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
  		void RenderCity (
			std::map<Color, std::vector<Coordinate>> coordinatesPerColor,
			Coordinate placement
		);
  		void Render();
  		void UpdateWindowTitle(int score, int fps);
  		void poll();

 	private:
  		SDL_Window *sdl_window;
  		SDL_Renderer *sdl_renderer;

  		const std::size_t screen_width;
  		const std::size_t screen_height;
  		const std::size_t grid_width;
  		const std::size_t grid_height;
};

#endif