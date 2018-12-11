#pragma once
#include "GameObject.h"

#define CANDLE_TEX "Resource\\Object\\Object.png"


#define CANDLE_STATE_BURN		 0
#define CANDLE_STATE_DIE		 1

#define CANDLE_BBOX_WIDTH		16
#define CANDLE_BBOX_HEIGHT		32

class LargeCandles : public GameObject
{
private:
	int width, height;
	int typeDroppedItem;

public:
	LargeCandles(int dropItem);
	~LargeCandles();

	int GetDropItem() { return typeDroppedItem; }

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);

	CollisionBox GetBoundingBox();

	void SetCellsOffSet(float cellWidth, float cellHeight);
	vector<D3DXVECTOR2> GetCellsOffSet() { return this->cellsOffset; }

	void LoadAnimation();
};


class SmallCandles : public GameObject
{
private:
	int width, height;
	int typeDroppedItem;

public:
	SmallCandles(int dropItem);
	~SmallCandles();

	int GetDropItem() { return typeDroppedItem; }

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);

	CollisionBox GetBoundingBox();

	void SetCellsOffSet(float cellWidth, float cellHeight);

	void LoadAnimation();
};