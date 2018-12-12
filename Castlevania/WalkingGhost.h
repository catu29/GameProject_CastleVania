#pragma once
#include "GameObject.h"

class WalkingGhost : public GameObject
{
private:
public:
	WalkingGhost();
	~WalkingGhost();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects);
	void Render(ViewPort * camera);
	void SetState(int state);

	void SetCellsOffSet(float cellWidth, float cellHeight);
	void UpdateCells();

	CollisionBox GetBoundingBox();
};

