#pragma once
#include "Scene.h"
#include "Define.h"
#define TEX_GAME_MENU "Resource\\GameMenuScene\\GameMenu.png"


class GameMenuScene : public Scene
{
private:

public:
	GameMenuScene();
	~GameMenuScene();

	void Update(DWORD dt);
	void Initialize();
	void Draw();
	void DestroyAll();

	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState();

	bool GetChangingStage() { return Scene::GetChangingStage(); }
	void SetChangingStage(bool _isChangeStage) { Scene::SetChangingStage(_isChangeStage); }

	ViewPort * GetCurrentCamera() { return NULL; }

};


