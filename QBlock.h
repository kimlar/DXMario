#pragma once

#include "GameObject.h"

class QBlock : public GameObject
{
public:
	// Constructor
	QBlock(wchar_t* filename, Graphics* gfx, float x, float y);

	// Destructor
	~QBlock();
};