#pragma once

#include "GameLevel.h"

class Level1 : public GameLevel
{
	float y;
	float ySpeed;

	

	Ground* cGround;

	Mario* cMario;

	QBlock* cQBlock;


	Font* font;

	float dt;

public:
	void Load() override;
	void Unload() override;
	void Update(float dt) override;
	void Render() override;
};