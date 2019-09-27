#include "GameController.h"

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>


GameLevel* GameController::currentLevel;
bool GameController::Loading;
double GameController::fps_dt;
double GameController::fps;
double GameController::fps_count;
std::string GameController::strFPS;
std::string GameController::strDT;
bool GameController::Keyboard[256] = {0};

GameController::GameController()
{
	fps = fps_dt = 0.0;
	fps_count = 0.0;
}

void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

void GameController::Update(float dt)
{
	
	fps_dt += dt;
	fps_count++;
	if (fps_dt >= 1.0)
	{
		// FPS computation
		fps = (double)fps_count + (fps_dt - 1.0);
		fps_dt = 0.0;
		fps_count = 0;

		// FPS as string
		std::ostringstream ss;
		ss.precision(5);
		ss << std::fixed << GameController::fps;
		strFPS = ss.str();

		// DT as string (delta time)
		std::ostringstream ss2;
		ss2.precision(5);
		ss2 << std::fixed << dt;
		strDT = ss2.str();
	}

	if (Loading) return;
	currentLevel->Update(dt);
}

void GameController::Render()
{
	if (Loading) return;
	currentLevel->Render();
}
