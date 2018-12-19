#pragma once
#include "GameObject.h"
#include "Candles.h"
#include "WalkingGhost.h"

#define NORMAL_WHIP				0
#define LIGHTNING_STAR_WHIP		1
#define VAMPIRE_KILLER_WHIP		2

#define WHIP_BBOX_HEIGHT		8
#define NORMAL_BBOX_WIDTH		28
#define SPECIAL_BBOX_WIDTH		46

#define WHIP_STATE_ATTACK		1

class Whip : public GameObject
{
private:
	static Whip * _instance;
	int type;
	
public:
	Whip();
	~Whip();

	static Whip * GetInstance();

	void LoadAnimation();
	void SetPosition(D3DXVECTOR3 _simonPosition, bool isStanding, float dir); 

	int GetType() { return this->type; }
	void SetType(int _type) { type = _type; }

	CollisionBox GetBoundingBox();
	void CalPotentialCollision(vector<LPGAMEOBJECT> *coliableObjects, vector<LPCOLLISIONEVENT> &coliableEvents);
	void HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);

	void Render(ViewPort * camera);
};

