#pragma once

#include "GameObject.h"

class Mario : public GameObject
{
	float dt;
	float speedMax;
	bool IsMarioOnGround;
public:
	// Constructor
	Mario(wchar_t* filename, Graphics* gfx, float x, float y);

	// Destructor
	~Mario();
	
	// Update
	void Update(float dt);

	// Draw the bitmap to the render target
	void Draw();

	// Controller
	void Controller(bool *keyboard);
	
	// Physics
	void Physics();

	// Mario is/set on ground
	void SetMarioOnGround(bool onGround);
	bool GetMarioOnGround();

	//bool IsDucking;
	//bool IsJumping;

	float JumpGainLeft;
	bool HasReleasedJump;


	// Input controller
	bool keyJump;
	bool keyLeft;
	bool keyRight;
	bool keyDuck;

	// Current sprite action;
	enum class Action
	{
		Idle = 0,
		WalkLeft,
		WalkRight,
		Jump,
		Duck,
		JumpDuck
	};
	Action action;
	
};