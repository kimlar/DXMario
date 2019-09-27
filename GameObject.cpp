#include <fstream>
#include <sstream>
#include "GameObject.h"
#include "ImageLoader.h"

GameObject::GameObject(wchar_t* filename, Graphics* gfx, float x, float y)
{
	this->gfx = gfx;	// Save the gfx parameter for later
	bmp = NULL;			// NULL our ID2D1Bitmap to start with

	ImageLoader* im = new ImageLoader(filename, gfx);
	bmp = im->GetImage();

	//=========================================================================
	this->x = x;
	this->y = y;
	frame_flip = false;
	frame = 0;
	frame_last = 0;
	frame_time = 0.0f;
	frame_delay = 0.0f;
	frame_tagname = "Idle";
}

GameObject::~GameObject()
{
	if (bmp) bmp->Release();
}

void GameObject::Draw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,	// Bitmap
		D2D1::RectF(x, y, x+bmp->GetSize().width, y+bmp->GetSize().height),				// Destination rectangle
		1.0f,	// Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	// Interpolation
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)				// Source rectangle
		);
}

// Draw a sub area
void GameObject::DrawSub(float x1, float y1, float x2, float y2)
{
	if (frame_flip)
	{
		gfx->GetRenderTarget()->SetTransform(
				D2D1::Matrix3x2F::Scale(
					D2D1::Size(-1.0f, 1.0f),
					D2D1::Point2F(x + 18, 500))
				);


		gfx->GetRenderTarget()->DrawBitmap(
			bmp,	// Bitmap
			D2D1::RectF(x, y, x + (x2 - x1), y + (y2 - y1)),				// Destination rectangle
			1.0f,	// Opacity
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	// Interpolation
			D2D1::RectF(x1, y1, x2, y2)				// Source rectangle
			);

		gfx->GetRenderTarget()->SetTransform(
			D2D1::Matrix3x2F::Scale(
				D2D1::Size(1.0f, 1.0f),
				D2D1::Point2F(x, 500))
			);
	}
	else
	{
		gfx->GetRenderTarget()->SetTransform(
			D2D1::Matrix3x2F::Scale(
				D2D1::Size(1.0f, 1.0f),
				D2D1::Point2F(x, 500))
			);

		gfx->GetRenderTarget()->DrawBitmap(
			bmp,	// Bitmap
			D2D1::RectF(x, y, x + (x2 - x1), y + (y2 - y1)),				// Destination rectangle
			1.0f,	// Opacity
			D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	// Interpolation
			D2D1::RectF(x1, y1, x2, y2)				// Source rectangle
			);
	}
}


// Draw the animation (tag name)
void GameObject::DrawAnimation()
{
	DrawSub(
		animation.at(frame_tagname)[frame].frame[0],
		animation.at(frame_tagname)[frame].frame[1],
		animation.at(frame_tagname)[frame].frame[2],
		animation.at(frame_tagname)[frame].frame[3]);
}

// Set the animation tag
void GameObject::SetAnimationTag(std::string tagname)
{
	frame_tagname = tagname;



	//std::string tagname
	//frame_last
}

// Set next frame
void GameObject::NextFrame()
{
	if (frame_time > frame_delay)
	{
		frame_time = 0.0f;
		frame++;
		if (frame > 2)
			frame = 0;
	}
}

// Set position X
void GameObject::SetPositionX(float x)
{
	this->x = x;
}
// Get position X
float GameObject::GetPositionX()
{
	return x;
}

// Set position Y
void GameObject::SetPositionY(float y)
{
	this->y = y;
}
// Get position Y
float GameObject::GetPositionY()
{
	return y;
}

// Set speed X
void GameObject::SetSpeedX(float x)
{
	xSpeed = x;
}
// Get speed X
float GameObject::GetSpeedX()
{
	return xSpeed;
}

// Set speed Y
void GameObject::SetSpeedY(float y)
{
	ySpeed = y;
}
// Get speed Y
float GameObject::GetSpeedY()
{
	return ySpeed;
}

// Load UV data from file
void GameObject::LoadAnimationData(wchar_t * filename)
{
	float x1 = 0.0f;
	float y1 = 0.0f;
	float x2 = 0.0f;
	float y2 = 0.0f;
	
	//
	// Parse file
	//
			
	// Read file to memory array
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> memfile;
	while (std::getline(infile, line))
		memfile.push_back(line);
	
	// Read frame_delay
	if (memfile[0].substr(0, std::string("frame_delay =").length()) == "frame_delay =")
	{
		std::string buf = memfile[0].substr(memfile[0].find('=')+1);
		if (buf[0] == ' ')
			buf = buf.substr(1);
		
		std::istringstream iss(buf);
		iss >> frame_delay;
	}
	
	// Begin parsing from memory array
	std::vector<Frame> vfra;
	GameObject::Frame tfra;
	std::string currentTag = "";
	for (int i = 2; i < memfile.size(); i++) //starts from line 2
	{
		// End of frames for this tag
		if (memfile[i] == "")
		{
			if (currentTag != "")
			{
				animation.emplace(currentTag, vfra);
				vfra.clear();
			}
			currentTag = "";
			continue;
		}
		// New tag found
		if (memfile[i].at(memfile[i].length() - 1) == ':')
		{
			currentTag = memfile[i].substr(0, memfile[i].length() - 1);
			continue;
		}

		// Add UV data for frame
		std::string buf; // Have a buffer string
		std::stringstream ss(memfile[i]); // Insert the string into a stream
		int it = 0;
		while (ss >> buf)
		{
			std::istringstream iss(buf);
			iss >> tfra.frame[it++];
		}
		vfra.push_back(tfra);

	}
	animation.emplace(currentTag, vfra);
	vfra.clear();

}
