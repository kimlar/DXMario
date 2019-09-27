#include "Mario.h"


Mario::Mario(wchar_t* filename, Graphics* gfx, float x, float y) : GameObject(filename, gfx, x, y)
{
	IsMarioOnGround = true;
	
	JumpGainLeft = 0.0f;
	HasReleasedJump = false;

	// Input controller
	keyJump = false;
	keyLeft = false;
	keyRight = false;
	keyDuck = false;

	// Current sprite action
	action = Action::Idle;

	LoadAnimationData(L"mario-frames.txt");
	
}

Mario::~Mario()
{

}

// Update
void Mario::Update(float dt)
{
	this->dt = dt;

	frame_time += dt;

	action = Mario::Action::Idle;


	if (keyLeft)
		action = Action::WalkLeft;
	else if (keyRight)
		action = Action::WalkRight;
	if (keyLeft && keyRight)
		action = Action::Idle;


	if (action == Action::WalkLeft || action == Action::WalkRight)
	{
		if (GetMarioOnGround() && !keyDuck)
			SetAnimationTag("Walk");

		if (action == Action::WalkLeft)
			frame_flip = true;
		else
			frame_flip = false;

		if (!GetMarioOnGround() || !keyDuck)
		{
			if (action == Action::WalkLeft)
				SetPositionX(GetPositionX() - 200.0f * dt);
			else
				SetPositionX(GetPositionX() + 200.0f * dt);

			NextFrame();
		}
	}




	if (keyJump)
	{
		if (GetMarioOnGround() && HasReleasedJump)
		{
			JumpGainLeft = 660.0f;
			SetMarioOnGround(false);
			
			HasReleasedJump = false;
		}

		JumpGainLeft -= 60.0f;
		if (JumpGainLeft > 0)
			SetSpeedY(GetSpeedY() - 60.0f * dt);
	}
	else
	{
		JumpGainLeft = 0.0f;
		if (GetMarioOnGround())
			HasReleasedJump = true;
	}


	if (!GetMarioOnGround() && !keyDuck)
	{
		frame = 0;
		SetAnimationTag("Jump");
	}

	if (keyDuck)
	{
		frame = 0;
		SetAnimationTag("Duck");
	}

	if (action == Action::Idle && GetMarioOnGround() && !keyDuck)
	{
		frame = 0;
		SetAnimationTag("Idle");
	}

	Physics();
}

// Draw the bitmap to the render target
void Mario::Draw()
{
	DrawAnimation();
}

// Controller
void Mario::Controller(bool *keyboard)
{
	if (keyboard[87]) { keyJump = true; }	else { keyJump = false; }
	if (keyboard[65]) { keyLeft = true; }	else { keyLeft = false; }
	if (keyboard[68]) { keyRight = true; }	else { keyRight = false; }
	if (keyboard[83]) { keyDuck = true; }	else { keyDuck = false; }
}

// Physics
void Mario::Physics()
{
	// Mario is affected by physics
	SetSpeedY(GetSpeedY() + 15.0f * dt);
	SetPositionY(GetPositionY() + GetSpeedY());

	// Mario hit the ground
	if (GetPositionY() > 446.0f)
	{
		SetPositionY(446.0f);
		SetSpeedY(0.0f);

		SetMarioOnGround(true);
	}
}

// Mario is/set on ground
void Mario::SetMarioOnGround(bool onGround)
{
	IsMarioOnGround = onGround;
}
bool Mario::GetMarioOnGround()
{
	return IsMarioOnGround;
}
