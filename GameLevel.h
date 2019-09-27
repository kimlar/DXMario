#pragma once

#include "Graphics.h"
#include "Font.h"

// Shared amoung Level1.h, Level2.h etc..
#include "Mario.h"
#include "Ground.h"
#include "QBlock.h"

class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};
