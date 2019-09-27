#pragma once

#include <wincodec.h>	// WIC coder header for decoding images from file. Link to: windowscodecs.lib
#include "Graphics.h"	// Includes windows and d2d1.h


class Font
{
	Graphics* gfx;		// Reference to graphics class
	ID2D1Bitmap* bmp;	// Bitmap loaded file and converted to Direct2D format

	float fx_org;		// Original placement
	float fy_org;		// Original placement
	float fx;			// Font x, where to draw on the screen. Just like a cursor.
	float fy;			// Font y, where to draw on the screen. Just like a cursor.
public:
	Font(wchar_t* filename, Graphics* gfx);

	~Font();
	
	//void Draw(); // SHOW THE HOLE PNG
	void DrawString(char* text, float x, float y);
	void DrawChar(char ch);
};