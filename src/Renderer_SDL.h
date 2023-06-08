#ifndef RENDERER_SDL_H
#define RENDERER_SDL_H

#include <vector>

#include "Color.h"
#include "Coordinate.h"
#include "Rect.h"
#include "Renderer.h"
#include "SDL.h"
#include "TextRect.h"

class Renderer_SDL : public Renderer {
public:
	Renderer_SDL (
		const std::size_t screen_width,
		const std::size_t screen_height,
		std::string title);
	~Renderer_SDL();
	Renderer_SDL () = delete;
    Renderer_SDL (const Renderer_SDL& o) = delete;
    Renderer_SDL (Renderer_SDL&& o) noexcept = delete;
    Renderer_SDL& operator= (const Renderer_SDL& o) = delete;
    Renderer_SDL& operator=(Renderer_SDL&& o) noexcept = delete;
		
	void startFrame() override;
	void endFrame() override;

	void fillBlock (Rect blocks, const std::vector<uint8_t>& rgba) override;

	void fillBlocks (const std::vector<Rect>& blocks, const std::vector<uint8_t>& rgba) override;

	void fillBlock (
		int width, 
		int height,
		Coordinate coordinate,
		const std::vector<uint8_t>& rgba
	) override;

	void fillBlocks(
		int width,
		int height,
		const std::vector<Coordinate>& coordinates,
		const std::vector<uint8_t>& rgba
	) override;

	void renderText (
		int x, 
		int y,
		std::string textString,
		int letterHeight, 
		double widthMultiplier, 
		const std::vector<uint8_t>& rgbaText,
		const std::vector<uint8_t>& rgbaBackground,
		int position
	) override;

	void renderTexts (const std::vector<TextRect>& texts);
	
private:
	SDL_Window *_sdl_window;
	SDL_Renderer *_sdl_renderer;

	const std::size_t _screen_width;
	const std::size_t _screen_height;

	bool initRenderer ();
	bool initVideo ();
	bool initWindow (std::string title);
	bool linuxSettings ();
	
};

#endif