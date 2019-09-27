#pragma once

#include <wincodec.h>	// WIC coder header for decoding images from file. Link to: windowscodecs.lib
#include "Graphics.h"	// Includes windows and d2d1.h

class ImageLoader
{
	Graphics* gfx;		// Reference to graphics class
	ID2D1Bitmap* bmp;	// Bitmap loaded file and converted to Direct2D format
public:
	// Constructor
	ImageLoader(wchar_t* filename, Graphics* gfx);

	// Destructor
	~ImageLoader();

	// Draw the bitmap to the render target
	//void Draw();

	// Give pointer to image
	ID2D1Bitmap* GetImage();

};
