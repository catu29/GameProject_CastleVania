#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Graphics.h"
#include "InputDevice.h"
#include "SceneManager.h"
#include "Database.h"


#define GAME_WINDOWED true
#define FRAMERATE 60

class Game
{
private:
	static Game * __instance;

	HWND hWnd;

public:
	bool Initialize(HWND hWnd);

	void Run();
	void Update(DWORD gameTime);
	void Render(DWORD gameTime);

	static Game * GetInstance();
	Game();
	~Game();
};


