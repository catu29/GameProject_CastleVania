#pragma once
#include "GameObject.h"
#include "ViewPort.h"

#define SW_KNIFE		0
#define SW_BOOMERANG	1
#define SW_AXE			2
#define SW_HOLYWATER	3
#define SW_STOPWATCH	4


class SubWeapons : public GameObject
{
private:
	int type;
	static SubWeapons * _instance;

public:
	SubWeapons();
	~SubWeapons();

	static SubWeapons * GetInstance();

	bool IsInCameraView(ViewPort * camera);

	int GetType() { return this->type; }
	void SetType(int _type);

	void SetPosition(D3DXVECTOR3 _simonPosition, bool isStanding, float direction);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);

	void HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);

	CollisionBox GetBoundingBox();
};

