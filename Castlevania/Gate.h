#pragma once
#include "GameObject.h"

#define GATE_STATE_NORMAL			0
#define GATE_STATE_OPEN				1
#define GATE_STATE_CLOSE			2

#define GATE_ANI_NORMAL_OPEN		0
#define GATE_ANI_NORMAL_CLOSE		1
#define GATE_ANI_OPEN_RIGHT			2
#define GATE_ANI_CLOSE_RIGHT		3

class Gate : public GameObject
{
private:
	bool isOpening;

public:
	Gate();
	~Gate();

	void LoadAnimation();

	void Render(ViewPort * camera);
	CollisionBox GetBoundingBox();

	void SetCellsOffSet(float cellWidth, float cellHeight);

	bool IsOpening() { return this->isOpening; }
	void SetOpen(bool op) { this->isOpening = op; }

	void SetState(int state);
};