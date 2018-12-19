#include "Gate.h"
#include "Grid.h"
#include "Simon.h"

Gate::Gate() : GameObject()
{
	state = GATE_STATE_NORMAL;
	tag = TAG_GATE;

	isOpening = false;
}

Gate::~Gate()
{
}

void Gate::LoadAnimation()
{
	AddAnimation(504);
	AddAnimation(505);
	AddAnimation(506); // 2 Open gate left to right
	AddAnimation(507); // 3 Close gate left to right
}

void Gate::SetState(int state)
{
	GameObject::SetState(state);

	switch (state)
	{
	case GATE_STATE_OPEN:
		if (GetTickCount() - stateTime >= 300) // 3 frames
		{
			state = GATE_STATE_NORMAL;

			if (direction.x > 0)
			{
				Simon::GetInstance()->SetState(SIMON_STATE_WALKING_RIGHT);
			}
			else if (direction.x < 0)
			{
				Simon::GetInstance()->SetState(SIMON_STATE_WALKING_LEFT);
			}
		}
		break;
	case GATE_STATE_CLOSE:
		if (GetTickCount() - stateTime >= 300) // 3 frames
		{
			state = GATE_STATE_NORMAL;
		}
		break;
	}
}
void Gate::Render(ViewPort * camera)
{
	int ani;

	switch (state)
	{
	case GATE_STATE_NORMAL:
		if (isOpening)
		{
			ani = GATE_ANI_NORMAL_OPEN;
		}
		else
		{
			ani = GATE_ANI_NORMAL_CLOSE;
		}
		break;

	case GATE_STATE_OPEN:
		if (direction.x == 1)
		{
			ani = GATE_ANI_OPEN_RIGHT;
		}
		/*else if (direction.x == -1)
		{
			ani = GATE_ANI_OPEN_LEFT;
		}*/

		break;

	case GATE_STATE_CLOSE:
		if (direction.x == 1)
		{
			ani = GATE_ANI_CLOSE_RIGHT;
		}
		/*else if (direction.x == -1)
		{
			ani = GATE_ANI_CLOSE_LEFT;
		}*/
		break;
	}

	D3DXVECTOR3 viewPortPos = this->position;
	D3DXVECTOR3 p(0, 0, 0);
	CollisionBox b = this->GetBoundingBox();

	p.x = b.left;
	p.y = b.top;

	if (camera != NULL)
	{
		viewPortPos = camera->ConvertPosInViewPort(this->position);
		p = camera->ConvertPosInViewPort(this->position);
	}

	animations[ani]->Render(viewPortPos.x, viewPortPos.y);
	RenderBoundingBox(p.x, p.y);
}

CollisionBox Gate::GetBoundingBox()
{
	return CollisionBox(position.x, position.y, position.x + 8, position.y + 32);
}

void Gate::SetCellsOffSet(float cellWidth, float cellHeight)
{
	this->cellsOffset.clear();

	CollisionBox b(this->GetBoundingBox().left, this->GetBoundingBox().top, this->GetBoundingBox().right, this->GetBoundingBox().bottom);

	if (b.right < 0 || b.bottom < 0 || b.top > Grid::GetInstance()->GetGridHeight() || b.left > Grid::GetInstance()->GetGridWidth())
		return;

	if (b.left < 0)
		b.left = 0;

	if (b.top < 0)
		b.top = 0;

	if (b.right > Grid::GetInstance()->GetGridWidth())
		b.right = Grid::GetInstance()->GetGridWidth();

	if (b.bottom > Grid::GetInstance()->GetGridHeight())
		b.bottom = Grid::GetInstance()->GetGridHeight();

	int cellLeft = b.left / cellWidth;
	int cellTop = b.top / cellHeight;
	int cellRight = cellLeft;

	if (((b.right / cellWidth) - (int)(b.right / cellWidth)) == 0)
	{
		cellRight = b.right / cellWidth - 1;
	}
	else
	{
		cellRight = b.right / cellWidth;
	}

	int cellBottom = cellTop;

	if (((b.bottom / cellHeight) - (int)(b.bottom / cellHeight)) == 0)
	{
		cellBottom = b.bottom / cellHeight - 1;
	}
	else
	{
		cellBottom = b.bottom / cellHeight;
	}

	if (cellRight < cellLeft || cellBottom < cellTop)
		return;

	// Object offset in grid
	for (UINT row = cellTop; row <= cellBottom; row++)
	{
		for (UINT col = cellLeft; col <= cellRight; col++)
		{
			cellsOffset.push_back(D3DXVECTOR2(row, col));
			Grid::GetInstance()->Add(D3DXVECTOR2(row, col), this);
		}
	}
}