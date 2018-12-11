#pragma once
#include "GameObject.h"
#include "Item.h"

#define BRICK_TYPE_GROUND		0
#define BRICK_TYPE_WALL			1
#define BRICK_TYPE_ITEM			2
#define BRICK_TYPE_CHANGE		3
#define BRICK_TYPE_PRE_CHANGE	4

class Brick : public GameObject
{
private:
	int type;
	int specialItemType;
	bool isStatic;
	Item * specialItem;

public:
	Brick(int type);
	~Brick();

	int GetType() { return this->type; }
	void SetType(int type) { this->type = type; }

	int GetState() { return this->state; }

	void SetMoving(bool isMove = true) { this->isStatic = !isMove; }
	bool CanMove() { return !isStatic; }

	void SetCellsOffSet(float cellWidth, float cellHeight);
	vector<D3DXVECTOR2> GetCellsOffSet() { return this->cellsOffset; }
	void UpdateCells();

	Item * GetSpecialItem() { return this->specialItem; }
	void SetSpecialItem(Item * item) { this->specialItem = item; }

	int GetSpecialItemType() { return this->specialItemType; }
	void SetSpecialItemType(int itemType) { this->specialItemType = itemType; }

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);
	CollisionBox GetBoundingBox();
};