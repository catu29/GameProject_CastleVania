#pragma once
#include "GameObject.h"
#include "Candles.h"

#define NORMAL_WHIP 0
#define SMALL_WHIP 1
#define RED_WHIP 2
#define YELLOW_WHIP 3
#define BLUE_WHIP 4
#define VIOLET_WHIP 5

#define WHIP_BBOX_HEIGHT 8
#define NORMAL_BBOX_WIDTH 28
#define SPECIAL_BBOX_WIDTH 46

#define WHIP_STATE_ATTACK 1

#define WHIP_TEX "Resource\\Weapons\\Whip.png"

class Whip : public GameObject
{
private:
	static Whip * _instance;
	int type;
	DWORD frameTime;
	
public:
	Whip();
	~Whip();

	static Whip * GetInstance();

	void LoadAnimation();
	void SetPosition(D3DXVECTOR3 _simonPosition, bool isStanding, float dir); 

	int GetType() { return this->type; }
	void SetType(int _type) { type = _type; }

	CollisionBox GetBoundingBox();
	void HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);

	void Render(ViewPort * camera);
};

