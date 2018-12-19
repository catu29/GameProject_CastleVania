#include "WalkingGhost.h"
#include "Bricks.h"
#include "Grid.h"


WalkingGhost::WalkingGhost()
{
	tag = TAG_WALKING_GHOST;
}


WalkingGhost::~WalkingGhost()
{

}

void WalkingGhost::CalPotentialCollision(vector<LPGAMEOBJECT>* colliableObjects, vector<LPCOLLISIONEVENT>& colliableEvents)
{
	for (UINT i = 0; i < colliableObjects->size(); i++)
	{
		if (colliableObjects->at(i)->GetTag() == TAG_LARGE_CANDLE || colliableObjects->at(i)->GetTag() == TAG_SMALL_CANDLE
			|| colliableObjects->at(i)->GetTag() == TAG_WALKING_GHOST || colliableObjects->at(i)->GetTag() == TAG_ITEM
			|| colliableObjects->at(i)->GetTag() == TAG_STAIR)
		{
			continue;
		}
		else
		{
			LPCOLLISIONEVENT e = new CollisionEvent(-1, 0, 0, colliableObjects->at(i));

			if (this->vx == 0 && this->vy == 0)
			{
				CollisionBox b1 = this->GetBoundingBox();

				CollisionBox b2 = colliableObjects->at(i)->GetBoundingBox();

				if (AABB(b1, b2))
				{
					e = new CollisionEvent(0, -(this->direction.x), -(this->direction.y), colliableObjects->at(i));
				}
			}
			else
			{
				e = SweptAABBEx(colliableObjects->at(i));
			}

			if (e->Get_t() >= 0.0f && e->Get_t() < 1.0f)
				colliableEvents.push_back(e);
			else
				delete e;
		}
	}

	std::sort(colliableEvents.begin(), colliableEvents.end());
}

/*
Calculate which cells it is living on
*/
void WalkingGhost::SetCellsOffSet(float cellWidth, float cellHeight)
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

/*
Update which cells it is living if it has moved
*/
void WalkingGhost::UpdateCells()
{
	// If object has not moved, stop checking
	if (this->dx == 0 && this->dy == 0)
		return;

	vector<D3DXVECTOR2> oldList(cellsOffset); // Store old values to remove from old cells

	for (UINT i = 0; i < oldList.size(); i++)
	{
		Grid::GetInstance()->Remove(oldList[i], this);
	}

	oldList.clear();

	SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());
}

void WalkingGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);

	vy += 0.1f;
	vx = 0.05f * direction.x;

	vector<LPCOLLISIONEVENT> colliableEvents;
	vector<LPCOLLISIONEVENT> colliableResults;

	colliableEvents.clear(); // Make sure no events remain

	if (state != STATE_DIE)
	{
		CalPotentialCollision(colliableObjects, colliableEvents);

		if (colliableEvents.size() == 0)
		{
			position.x += dx;
			position.y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(colliableEvents, colliableResults, min_tx, min_ty, nx, ny);

			position.y += dy * min_ty + ny * 0.4f;
			position.x += dx * min_tx;

			if (ny != 0)
				vy = 0;

			for (UINT i = 0; i < colliableResults.size(); i++)
			{
				if (dynamic_cast<Brick *>(colliableResults[i]->GetObj()))
				{
					Brick * br = dynamic_cast<Brick *>(colliableResults[i]->GetObj());

					if (br->GetType() == BRICK_TYPE_WALL)
					{
						direction.x *= -1;
						vx *= direction.x;
					}
				}
			}
		}

		for (UINT i = 0; i < colliableEvents.size(); i++)
			delete colliableEvents[i];

		UpdateCells();
	}

}
void WalkingGhost::Render(ViewPort * camera)
{
	D3DXVECTOR3 viewPortPos = camera->ConvertPosInViewPort(this->position);
	
	switch (state)
	{
	case STATE_LIVE:
		if (direction.x > 0)
		{
			Animations::GetInstance()->GetAnimation(901)->Render(viewPortPos.x, viewPortPos.y);
		}
		else if (direction.x < 0)
		{
			Animations::GetInstance()->GetAnimation(900)->Render(viewPortPos.x, viewPortPos.y);
		}
		break;
	case STATE_DIE:
		Animations::GetInstance()->GetAnimation(501)->Render(viewPortPos.x, viewPortPos.y + 8);
		Animations::GetInstance()->GetAnimation(502)->Render(viewPortPos.x + 8, viewPortPos.y + 11);
		break;
	}

	CollisionBox b = this->GetBoundingBox();
	D3DXVECTOR3 p = this->position;
	p.x = b.left;
	p.y = b.top;
	p = camera->ConvertPosInViewPort(p);

	RenderBoundingBox(p.x, p.y);
}

void WalkingGhost::SetState(int state)
{
	GameObject::SetState(state);
}

CollisionBox WalkingGhost::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	b.left = position.x;
	b.top = position.y - 1;
	b.right = b.left + 16;
	b.bottom = b.top + 32;

	return b;
}
