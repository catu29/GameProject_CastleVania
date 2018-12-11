#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Textures.h"
#include "Animations.h"
#include "InputDevice.h"
#include "GameObject.h"
#include "TileMap.h"
#include "UI.h"

class Scene
{
protected:
	int currentMap;
	
	vector<TileMap*> listMap;

	UI * ui;

	bool isChangeStage;
	float gameTime;

	bool isChangeMap;
public:
	Scene();
	~Scene() {};

	virtual void Update(DWORD dt);
	virtual void LoadResource();
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void DestroyAll() = 0;

	virtual void OnKeyUp(int keyCode) = 0;
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void KeyState() = 0;
	virtual bool GetChangingStage() { return this->isChangeStage; }
	virtual void SetChangingStage(bool _isChangeStage) { this->isChangeStage = _isChangeStage; }

	void SetChangingMap(bool isChangeMap) { this->isChangeMap = isChangeMap; }


	TileMap * GetCurrentMap() { return this->listMap[currentMap]; }
};

