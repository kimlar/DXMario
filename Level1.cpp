#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"

void Level1::Load()
{
	/*
	y = 0.0f;
	ySpeed = 0.0f;
	*/

	
	font = new Font(L"Consolas14.png", gfx);

	// Level
	cGround = new Ground(L"green-ground.png", gfx, 0.0f,500.0f);
	cMario = new Mario(L"mario.png", gfx, 400.0f, 500.0f);
	cQBlock = new QBlock(L"QBlock.png", gfx, 300.0f, 400.0f);


}

void Level1::Unload()
{
	delete font;

	delete cGround;

	delete cMario;

	delete cQBlock;

}

void Level1::Update(float dt)
{
	this->dt = dt;

	/*
	// Update!
	ySpeed += 1.0f;
	y += ySpeed;
	if (y > 500)
	{
		y = 500;
		ySpeed = -30.0f;
	}
	*/

	
	cMario->Controller(GameController::Keyboard);


	cMario->Update(dt);

}

void Level1::Render()
{
	gfx->ClearScreen(0.98f, 0.85f, 0.62f);

	

	cGround->Draw();


	gfx->DrawCircle(500.0f, 300.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f);



	if (GameController::Keyboard[(int)'T'])
	{

		// FPS
		font->DrawString("FPS:", 150, 100);
		font->DrawString((char*)GameController::strFPS.c_str(), 200, 100);

		// delta time (second)
		font->DrawString("dt:", 150, 120);
		font->DrawString((char*)GameController::strDT.c_str(), 200, 120);
	}

	cQBlock->Draw();

	cMario->Draw();


}
