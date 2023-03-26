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

	// draws a solid rectangle with the given color
	void fillBlock (Rect blocks, const std::vector<uint8_t>& rgba) override;

	// draws solid rectangles for the given blocks with the given color
	void fillBlocks (const std::vector<Rect>& blocks, const std::vector<uint8_t>& rgba) override;

	// draws a solid rectangle with the given dimensions, coordinates and color.
	// note @coordinates are in pixels.
	void fillBlock (
		int width, 
		int height,
		Coordinate coordinate,
		const std::vector<uint8_t>& rgba
	) override;

	// draws solid rectangles with the given dimentions, and corresponding coordinates and colors
	// in the vectors. note @coordinates are in pixels.
	void fillBlocks(
		int width,
		int height,
		const std::vector<Coordinate>& coordinates,
		const std::vector<uint8_t>& rgba
	) override;

	// Used to render text in window.
	// @x is the original top left corner of text block. The top left corner of text block will be
	//    moved depending on @position.
	// @y is the original top left corner of text block. The top left corner of text block will be
	//    moved depending on @position.
	// @textString is the text to be printed.
	// @widthMultiplier determines the spacing between letters. 
	//    The width of text block is widthMultiplier * letterHeight * textString length.
	// @text color is the text color.
	// @textBackgroundColor is the text background color
	// @position moves the top left corner of text block.
	// if @position is 1, then top left corner is moved to the left by half the width of
	//    the text block. Essentially centering the block horizontally, y does not change.
	// if @position is 2, then the top left corner is moved up by half the height of the
	//    text block up. Essentially centering the block vertically, x does not change.
	// if @position is 3, then the top left corner is moved to the left by the width of
	//    the text block and is moved up by half the height of the text block. 
	//    Essentially the block is aligned to the right side and centered vertically.
	// if @position is 4, then top left corner is not moved.
	// if @position is 5, then the top left corner is moved left by half the width of the
	//    block and is moved up by the height of the block. Essentially, the block is
	//    centered horizontally, and sits above the given @y coordinate.
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

	// prints the strings in the TextRects according to the TextRect attributes.
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