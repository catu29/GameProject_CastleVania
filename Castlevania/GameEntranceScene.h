#pragma once
#include "Scene.h"
#include "Gate.h"

#define MOVING_OBJECT_DATA_SOURCE		"Resource\\Object\\MovingObjectData.txt"


class GameEntranceScene : public Scene
{
private:
	vector<LPGAMEOBJECT> *listObjects;
	vector<LPGAMEOBJECT> *colliableObjects;

	Gate * gate1;
	Gate * gate2;

public:
	GameEntranceScene();
	~GameEntranceScene();

	void Update(DWORD dt);
	void Initialize();
	void LoadMap();
	void LoadObjects(int lv);
	void HandleDestroyedObjects();
	void Draw();
	void DestroyAll();
	void ChangeMap();

	void HandlePassGate(Gate * &gate);

	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState();

	bool GetChangingStage() { return Scene::GetChangingStage(); }
	void SetChangingStage(bool _isChangeStage) { Scene::SetChangingStage(_isChangeStage); }

	vector<LPGAMEOBJECT> *GetListObject() { return this->listObjects; }
};

