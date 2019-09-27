#include "Font.h"
#include "ImageLoader.h"

Font::Font(wchar_t* filename, Graphics* gfx)
{
	this->gfx = gfx;	// Save the gfx parameter for later
	bmp = NULL;			// NULL our ID2D1Bitmap to start with

	ImageLoader* im = new ImageLoader(filename, gfx);
	bmp = im->GetImage();

	//=========================================================================================
	fx_org = 0.0f;
	fy_org = 0.0f;
	fx = 0.0f;
	fy = 0.0f;
}

Font::~Font()
{
	if (bmp) bmp->Release();
}

/*
void Font::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,	// Bitmap
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),				// Destination rectangle
		1.0f,	// Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	// Interpolation
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)				// Source rectangle
		);
}
*/

void Font::DrawString(char* text, float x, float y)
{
	// Set up font
	fx_org = x;
	fy_org = y;
	fx = x;
	fy = y;
	
	// Draw each character
	for (int i = 0; i < strlen(text); i++)
		DrawChar(text[i]);
}

void Font::DrawChar(char ch)
{
	// If newline
	if (ch == '\n') { fx = fx_org; fy += bmp->GetSize().height; return; }
	if ((int)ch < 32 || (int)ch > 127) return;

	float u = 11.0f; // Char width: 11px

	float r = ((int)ch-31) * 11.0f; // Char position in png


	gfx->GetRenderTarget()->DrawBitmap(
		bmp,	// Bitmap
		D2D1::RectF(fx, fy, fx + u, fy + bmp->GetSize().height),				// Destination rectangle
		1.0f,	// Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	// Interpolation
		D2D1::RectF(r - u, 0.0f, r, bmp->GetSize().height)				// Source rectangle
		);

	// Update (next) position
	fx += 11.0f;
}
