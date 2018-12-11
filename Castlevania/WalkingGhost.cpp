#include "WalkingGhost.h"
#include "Bricks.h"


WalkingGhost::WalkingGhost()
{
	tag = TAG_WALKING_GHOST;
}


WalkingGhost::~WalkingGhost()
{

}

void WalkingGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);

	vy += 0.1f;
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

			for (UINT i = 0; i < colliableResults.size(); i++)
			{
				LPCOLLISIONEVENT e = colliableResults[i];

				if (e->GetObj()->GetTag() == TAG_LARGE_CANDLE)
				{
					if (e->Get_ny() != 0)
					{
						position.y += dy;
					}
					position.x += dx;
				}
				else if (e->GetObj()->GetTag() == TAG_ITEM)
				{
					if (e->Get_ny() != 0)
					{
						position.y += dy;
					}
					position.x += dx;
				}
				else if (e->GetObj()->GetTag() == TAG_BRICK)
				{
					Brick * br = dynamic_cast<Brick *>(colliableResults[i]->GetObj());
					if (br->GetType() == BRICK_TYPE_GROUND)
					{
						if (e->Get_ny() != 0)
						{
							vy = 0;
							vx = 0.05f * direction.x;
						}
						position.x += dx;
					}
					else if (br->GetType() == BRICK_TYPE_WALL)
					{
						if (e->Get_nx() != 0)
						{
							direction.x *= -1;
							vy = 0;
							vx = 0.05f * direction.x;
						}
						position.x += dx;
					}
					
				}
				

			}
		}

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
}
void WalkingGhost::SetState(int state)
{
	GameObject::SetState(state);
}

CollisionBox WalkingGhost::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	b.left = position.x;
	b.top = position.y;
	b.right = position.x + 16;
	b.bottom = position.y + 32;

	return b;
}
