#pragma once
#include "Scene.h"
#include "Define.h"
#include "Simon.h"
#include "GameObject.h"


//--------------------------------------------------------------
class GameIntroScene : public Scene
{
private:
	D3DXVECTOR3 simonPos, bat1Pos, bat2Pos, cloudPos;

public:
	GameIntroScene();
	~GameIntroScene();

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

