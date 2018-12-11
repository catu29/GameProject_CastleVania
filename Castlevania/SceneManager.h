#pragma once
#include "Scene.h"
#include "GameMenuScene.h"
#include "GameIntroScene.h"
#include "GameEntranceScene.h"

#define GAME_MENU_SCENE -1
#define GAME_INTRO_SCENE 0
#define GAME_ENTRANCE_SCENE 1



class SceneManager
{
private:
	static SceneManager * instance;
	Scene * currentScene;
	int sceneID;

public:
	static SceneManager * GetInstance();
	SceneManager();
	~SceneManager();

	bool Initialze(HWND hWnd);

	void LoadScene(int sceneID);

	void MoveToNextScene();

	void Update(DWORD dt);

	Scene * GetCurrentScene();
};

