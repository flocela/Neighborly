#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "Color.h"
#include "Coordinate.h"
#include "Rect.h"
#include "SDL.h"
#include "TextRect.h"

class Renderer {
public:
	Renderer (
		const std::size_t screen_width,
		const std::size_t screen_height,
		std::string title);
	~Renderer();
	Renderer () = delete;
    Renderer (const Renderer& o) = delete;
    Renderer (Renderer&& o) noexcept = delete;
    Renderer& operator= (const Renderer& o) = delete;
    Renderer& operator=(Renderer&& o) noexcept = delete;
		
	void startFrame();
	void endFrame();

	// draws a solid rectangles with the given color
	void fillBlock (Rect blocks, std::vector<uint8_t> rgba) ;

	// draws solid rectangles for the given blocks with the given color
	void fillBlocks (std::vector<Rect> blocks, std::vector<uint8_t> rgba);

	// draws a solid rectangle with the given dimensions, coordinates and color.
	// note @coordinates are in pixels.
	void fillBlock (
		int width, 
		int height,
		Coordinate coordinate,
		std::vector<uint8_t> rgba
	);

	// draws solid rectangles with the given dimentions, and corresponding coordinates and colors
	// in the vectors. note @coordinates are in pixels.
	void fillBlocks(
		int width,
		int height,
		std::vector<Coordinate> coordinates,
		std::vector<uint8_t> rgba
	);

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
		std::vector<uint8_t> rgbaText,
		std::vector<uint8_t> rgbaBackground,
		int position
	);

	// prints the strings in the TextRects according to the TextRect attributes.
	void renderTexts (std::vector<TextRect> texts);
	
private:
	SDL_Window *_sdl_window;
	SDL_Renderer *_sdl_renderer;

	const std::size_t _screen_width;
	const std::size_t _screen_height;

	bool initVideo ();
	bool linuxSettings ();
	bool initWindow (std::string title);
	bool initRenderer ();
};

#endif