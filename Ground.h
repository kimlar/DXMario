#pragma once

#include "GameObject.h"

class Ground : public GameObject
{
public:
	// Constructor
	Ground(wchar_t* filename, Graphics* gfx, float x, float y);

	// Destructor
	~Ground();
};