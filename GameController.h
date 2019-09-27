#pragma once

#include "GameLevel.h"
#include "Graphics.h"

#include <string>

class GameController
{

	GameController();
	static GameLevel* currentLevel;
public:
	static bool Loading;

	static double fps_dt;
	static double fps;
	static double fps_count;
	static std::string strFPS;
	static std::string strDT; //delta time

	static bool Keyboard[256]; // false: not pressed, true: pressed

	static void Init();

	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);

	static void Update(float dt);
	static void Render();
};