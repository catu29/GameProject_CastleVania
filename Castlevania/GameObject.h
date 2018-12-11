#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>
#include "ViewPort.h"
#include "Animations.h"


using namespace std;

#define TEX_BBOX_ID		7

#define STATE_DIE		-2
#define STATE_LIVE		-1

#define TAG_SIMON			0
#define TAG_WHIP			1
#define TAG_LARGE_CANDLE	2
#define TAG_ITEM			3
#define TAG_BRICK			4
#define TAG_STAIR			5
#define TAG_SMALL_CANDLE	6
#define TAG_WALKING_GHOST	7


class CollisionEvent;
typedef CollisionEvent * LPCOLLISIONEVENT;

class GameObject;
typedef GameObject * LPGAMEOBJECT;


//====================================================================
/*
This struct is for collision checking,
it has the same nature of bounding box,
and helps collision checking functions more simple
*/

struct CollisionBox
{
	float left;
	float top;
	float right;
	float bottom;

	CollisionBox(float l, float t, float r, float b)
	{
		left = l;
		top = t;
		right = r;
		bottom = b;
	}
};


//====================================================================
/*
This class is for storing results of a collision when it occurs
*/

class CollisionEvent
{
private:
	float t, nx, ny;
	LPGAMEOBJECT obj;
public:
	CollisionEvent(float t, int nx, int ny, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->obj = obj;
	}

	float Get_t() { return this->t; }
	int Get_nx() { return this->nx; }
	int Get_ny() { return this->ny; }
	LPGAMEOBJECT GetObj() { return this->obj; }
};


//====================================================================


class GameObject
{
protected:
	D3DXVECTOR3 position;
	vector<D3DXVECTOR2> cellsOffset;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	D3DXVECTOR2 direction;

	int tag;

	int state;
	int stateTime;
	DWORD startDieTime;
	bool canDestroy;

	DWORD dt;

	vector<LPANIMATION> animations;


public:
	bool CanDestroy() { return this->canDestroy; }

	void SetPosition(float x, float y) { this->position.x = x, this->position.y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetDirection(D3DXVECTOR2 _dir) { this->direction = _dir; }

	D3DXVECTOR3 GetPosition() { return this->position; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	D3DXVECTOR2 GetDirection() { return this->direction; }
	int GetTag() { return this->tag; }
	int GetState() { return this->state; }
	void GetDistance(float &dx, float &dy) { dx = this->dx; dy = this->dy; }
	vector<D3DXVECTOR2> GetCellsOffSet() { return this->cellsOffset; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	virtual void SetState(int state);

	virtual void Render(ViewPort * camera) = 0;
	virtual CollisionBox GetBoundingBox() = 0;

	void RenderBoundingBox(float x, float y);
	void AddAnimation(int aniId);

	bool AABB(CollisionBox box1, CollisionBox box2);
	void SweptAABB(CollisionBox mBox, CollisionBox sBox, float &t, float &nx, float &ny);
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coliableObject);
	void CalPotentialCollision(vector<LPGAMEOBJECT> *coliableObjects, vector<LPCOLLISIONEVENT> &coliableEvents);
	void FilterCollision(vector<LPCOLLISIONEVENT> &coliableEvents, vector<LPCOLLISIONEVENT> &coliableResult, float &min_tx, float &min_ty, float &nx, float &ny);

	GameObject();
	~GameObject();
};





