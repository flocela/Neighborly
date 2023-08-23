#ifndef Renderer__H
#define Renderer__H

#include <vector>

#include "Color.h"
#include "Coordinate.h"
#include "Rect.h"
#include "TextRect.h"

class Renderer {
	
public:
		
	virtual void endFrame() = 0;
	virtual void keepScreen() = 0;

	// draws solid rectangles for the given blocks with the given color
	virtual void fillBlocks (const std::vector<Rect>& blocks, const std::vector<uint8_t>& rgba) = 0;

	// draws a solid rectangle with the given dimensions, coordinates, and color.
	// note @coordinates are in pixels.
	virtual void fillBlock (
		int width, 
		int height,
		Coordinate coordinate,
		const std::vector<uint8_t>& rgba
	) = 0;

	// Used to render text in window.
	// x is the x-coordinate of the original top-left corner of text block. The top left corner of
	// text block will be moved depending on position.
	// y is the y-coordinate of the original top-left corner of text block. The top left corner of
	// text block will be moved depending on position.
	// textString is the text to be printed.
	// widthMultiplier determines the spacing between letters. 
	//    The width of text block is widthMultiplier * letterHeight * textString length.
	// rgbaText is the text color.
	// textBackgroundColor is the text background color
	// position moves the top left corner of text block.
	// if position is 1, then top left corner is moved to the left by half the width of
	//    the text block. Essentially centering the block horizontally, y does not change.
	// if position is 2, then the top left corner is moved up by half the height of the
	//    text block up. Essentially centering the block vertically, x does not change.
	// if position is 3, then the top left corner is moved to the left by the width of
	//    the text block and is moved up by half the height of the text block. 
	//    Essentially the block is aligned to the right side and centered vertically.
	// if position is 4, then top left corner is not moved.
	// if position is 5, then the top left corner is moved left by half the width of the
	//    block and is moved up by the height of the block. Essentially, the block is
	//    centered horizontally, and sits above the given @y coordinate.
	virtual void renderText (
		int x, 
		int y,
		std::string textString,
		int letterHeight, 
		double widthMultiplier, 
		const std::vector<uint8_t>& rgbaText,
		const std::vector<uint8_t>& rgbaBackground,
		int position
	) = 0;

	// prints the strings in the TextRects according to the TextRect attributes.
	virtual void renderTexts (const std::vector<TextRect>& texts) = 0;
	
private:
	
};

#endif