#pragma once

#include "InputDevice.h"
#include "GameObject.h"

#define SIMON_WALKING_SPEED							0.06f
#define SIMON_ONSTAIR_SPEED							0.02f
#define SIMON_JUMP_SPEED_Y							0.22f
#define SIMON_GRAVITY								0.014f

#define SIMON_STATE_IDLE_TURNBACK					-100
#define SIMON_STATE_IDLE							0
#define SIMON_STATE_WALKING_RIGHT					100
#define SIMON_STATE_WALKING_LEFT					200
#define SIMON_STATE_JUMP							300
#define SIMON_STATE_SIT								400
#define SIMON_STATE_ATTACK							500
#define SIMON_STATE_THROW							550
#define SIMON_STATE_CANCEL_ATTACK					600
#define SIMON_STATE_DIE								700
#define SIMON_STATE_UPSTAIR_RIGHT					900
#define SIMON_STATE_DOWNSTAIR_RIGHT					920
#define SIMON_STATE_UPSTAIR_LEFT					940
#define SIMON_STATE_DOWNSTAIR_LEFT					950
#define SIMON_STATE_IDLE_ON_STAIR					970



#define SIMON_ANI_IDLE_TURNBACK						0
#define SIMON_ANI_SIT_LEFT							1
#define SIMON_ANI_IDLE_LEFT							2
#define SIMON_ANI_WALKING_LEFT						3
#define SIMON_ANI_IDLE_UPSTAIRS_LEFT				4
#define SIMON_ANI_UPSTAIRS_LEFT						5
#define SIMON_ANI_IDLE_DOWNSTAIRS_LEFT				6
#define SIMON_ANI_DOWNSTAIRS_LEFT					7

#define SIMON_ANI_STAND_ATTACK_LEFT					8	
#define SIMON_ANI_SIT_ATTACK_LEFT					9
#define SIMON_ANI_UPSTAIRS_ATTACK_LEFT				10
#define SIMON_ANI_DOWNSTAIRS_ATTACK_LEFT			11

#define SIMON_ANI_STAND_GET_SPITEM_LEFT				12

#define SIMON_ANI_SIT_RIGHT							13
#define SIMON_ANI_IDLE_RIGHT						14
#define SIMON_ANI_WALKING_RIGHT						15
#define SIMON_ANI_IDLE_UPSTAIRS_RIGHT				16
#define SIMON_ANI_UPSTAIRS_RIGHT					17
#define SIMON_ANI_IDLE_DOWNSTAIRS_RIGHT				18
#define SIMON_ANI_DOWNSTAIRS_RIGHT					19

#define SIMON_ANI_STAND_ATTACK_RIGHT				20	
#define SIMON_ANI_SIT_ATTACK_RIGHT					21
#define SIMON_ANI_UPSTAIRS_ATTACK_RIGHT				22
#define SIMON_ANI_DOWNSTAIRS_ATTACK_RIGHT			23

#define SIMON_ANI_STAND_GET_SPITEM_RIGHT			24	

#define SIMON_BBOX_WIDTH							16
#define SIMON_STAND_BBOX_HEIGHT						31
#define SIMON_SIT_BBOX_HEIGHT						24
//--------------------------------------------------------

class Simon : public GameObject
{
private:
	static Simon * _instance;
	bool isSit;
	bool onStairRight;
	bool onStairLeft;
	bool canControlKeyboard;

	int totalWhip;
	int totalSubWeapon;

	D3DXVECTOR3 info; // hp, energy, life
	long score;

public:

	Simon();
	~Simon();
	static Simon * GetInstance();

	void LoadAnimation();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);
	void SetState(int state);

	void HandleMove();
	void HandleEvent(bool isKeyDown);

	CollisionBox GetBoundingBox();

	void SetInfo(D3DXVECTOR3 _info) { info = _info; }
	D3DXVECTOR3 GetInfo() { return info; }
	void SetScore(long) { this->score = score; }
	long GetScore() { return this->score; }

	void SetControlKB(bool canCtrl) { canControlKeyboard = canCtrl; }
	bool GetControlKB() { return this->canControlKeyboard; }
};

