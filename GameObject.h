#pragma once

#include <vector>
#include <map>
#include <wincodec.h>	// WIC coder header for decoding images from file. Link to: windowscodecs.lib
#include "Graphics.h"	// Includes windows and d2d1.h

class GameObject
{
	Graphics* gfx;		// Reference to graphics class
	ID2D1Bitmap* bmp;	// Bitmap loaded file and converted to Direct2D format

	float x;
	float y;
	float xSpeed;
	float ySpeed;

public:
	// Constructor
	GameObject(wchar_t* filename, Graphics* gfx, float x, float y);

	// Destructor
	~GameObject();

	// Draw the bitmap to the render target
	void Draw();

	// Draw a sub area
	void DrawSub(float x1, float y1, float x2, float y2);

	// Draw the animation (tag name)
	void DrawAnimation();

	// Set the animation tag
	void SetAnimationTag(std::string tagname);

	// Set next frame
	void NextFrame();

	// Set position X
	void SetPositionX(float x);
	// Get position X
	float GetPositionX();

	// Set position Y
	void SetPositionY(float y);
	// Get position Y
	float GetPositionY();

	// Set speed X
	void SetSpeedX(float x);
	// Get speed X
	float GetSpeedX();

	// Set speed Y
	void SetSpeedY(float y);
	// Get speed Y
	float GetSpeedY();

	bool frame_flip;	// Get/Set current frame-flipped horizontal	
	int frame; // Get/Set current frame number	
	int frame_last; // last of the current tag. Ex: Last frame in walking
	float frame_time; // Get/Set current frame-timestamp (time until next frame)
	float frame_delay; // time between two frames in seconds
	std::string frame_tagname;

	struct Frame
	{
		float frame[4]; // UV coordinate
	};

	std::map<std::string, std::vector<Frame>> animation;

	void LoadAnimationData(wchar_t* filename);

};