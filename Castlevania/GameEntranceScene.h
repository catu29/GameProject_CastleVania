#pragma once
#include "Scene.h"




class GameEntranceScene : public Scene
{
private:
	vector<LPGAMEOBJECT> *listObjects;
	vector<LPGAMEOBJECT> *colliableObjects;
public:
	GameEntranceScene();
	~GameEntranceScene();

	void Update(DWORD dt);
	void Initialize();
	void LoadMap();
	void HandleDestroyedObjects();
	void Draw();
	void DestroyAll();
	void ChangeMap();

	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState();

	bool GetChangingStage() { return Scene::GetChangingStage(); }
	void SetChangingStage(bool _isChangeStage) { Scene::SetChangingStage(_isChangeStage); }

	vector<LPGAMEOBJECT> *GetListObject() { return this->listObjects; }
};

