#pragma once
#include "GameObject.h"

#define ITEM_SMALL_HEART			0
#define ITEM_BIG_HEART				1
#define ITEM_WHIP_UPGRADE			2
#define ITEM_POT_ROAST				3
#define ITEM_MONEY_BAG_100			4
#define ITEM_MONEY_BAG_400			5
#define ITEM_MONEY_BAG_700			6
#define ITEM_MONEY_BAG_1000			7

#define ITEM_STOP_WATCH				8
#define ITEM_HOLY_WATER				9
#define ITEM_CROSS					10
#define ITEM_KNIFE					11
#define ITEM_AXE					12
#define ITEM_BOOMERANG				13

#define ITEM_INVINCIBILITY_POISION	14
#define ITEM_DOUBLE_SHOT			15
#define ITEM_TRIPLE_SHOT			16
#define ITEM_CRYSTAL_BALL			17

class Item : public GameObject
{
private:
	int type;
	DWORD bornTime;
public:
	Item(int type);
	~Item();

	int GetType() { return this->type; }

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);

	CollisionBox GetBoundingBox();

	void SetCellsOffSet(float cellWidth, float cellHeight);
	void UpdateCells();

	void HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void LoadAnimation();
};

