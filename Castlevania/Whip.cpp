
#include "Whip.h"
#include "Animations.h"
#include "Textures.h"

Whip::Whip()
{
	LoadAnimation();	
	state = 0;
	frameTime = 0;
}

Whip::~Whip()
{
}

Whip * Whip::_instance = NULL;

Whip * Whip::GetInstance()
{
	if (_instance == NULL) _instance = new Whip();
	return _instance;
}

void Whip::LoadAnimation()
{
	AddAnimation(100); // 0 animation nomal left
	AddAnimation(101); // 1 animation nomal left
	AddAnimation(102); // 2 animation red left
	AddAnimation(103); // 3 animation red left
	AddAnimation(104); // 4 animation short left
	AddAnimation(105); // 5 animation short left
	AddAnimation(106); // 6 animation yellow left
	AddAnimation(107); // 7 animation yellow left
	AddAnimation(108); // 8 animation blue left
	AddAnimation(109); // 9 animation blue left
	AddAnimation(110); // 10 animation violet left
	AddAnimation(111); // 11 animation violet left
}

void Whip::SetPosition(D3DXVECTOR3 _simonPosition, bool _isStanding, float dir)
{
	this->direction.x = dir;
	switch (type)
	{
	case NORMAL_WHIP: case SMALL_WHIP:
		if (_isStanding)
		{
			if (direction.x == -1)
			{
				position.x = _simonPosition.x - 22;
				position.y = _simonPosition.y + 3;
			}
			else if (direction.x == 1)
			{
				position.x = _simonPosition.x - 9;
				position.y = _simonPosition.y + 3;
			}
		}
		else
		{
			if (direction.x == -1)
			{
				position.x = _simonPosition.x - 22;
				position.y = _simonPosition.y + 10;
			}
			else if (direction.x == 1)
			{
				position.x = _simonPosition.x - 9;
				position.y = _simonPosition.y + 10;
			}
		}
		break;
	case YELLOW_WHIP: case RED_WHIP: case BLUE_WHIP: case VIOLET_WHIP:
		if (_isStanding)
		{
			if (direction.x == -1)
			{
				position.x = _simonPosition.x - 38;
				position.y = _simonPosition.y + 4;
			}
			else if (direction.x == 1)
			{
				position.x = _simonPosition.x - 8;
				position.y = _simonPosition.y + 4;
			}
		}
		else
		{
			if (direction.x == -1)
			{
				position.x = _simonPosition.x - 38;
				position.y = _simonPosition.y + 11;
			}
			else if (direction.x == 1)
			{
				position.x = _simonPosition.x - 8;
				position.y = _simonPosition.y + 11;
			}
		}
		break;
	}
}

void Whip::HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);
	frameTime += dt;

	if (frameTime >= 200)
	{
		vector<LPCOLLISIONEVENT> colliableEvents;
		vector<LPCOLLISIONEVENT> colliableResults;

		colliableEvents.clear(); // Make sure no events remain

		if (state == WHIP_STATE_ATTACK)
			CalPotentialCollision(colliableObjects, colliableEvents);

		if (colliableEvents.size() != 0)
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(colliableEvents, colliableResults, min_tx, min_ty, nx, ny);

			// Collision logic with candles
			for (UINT i = 0; i < colliableResults.size(); i++)
			{
				LPCOLLISIONEVENT e = colliableResults[i];

				if (e->GetObj()->GetTag() == TAG_LARGE_CANDLE)
				{
					if (dynamic_cast<LargeCandles *>(e->GetObj()))
					{
						LargeCandles *lc = dynamic_cast<LargeCandles *>(e->GetObj());
						if (lc->GetState() != STATE_DIE)
							lc->SetState(STATE_DIE);
					}
				}
			}
		}

		frameTime = 0;
	}
	
}

CollisionBox Whip::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	switch (type)
	{
	case NORMAL_WHIP:
	case SMALL_WHIP:
		if (this->direction.x == -1)
		{
			b.left = position.x;
			b.top = position.y + 6.0f;
			b.bottom = b.top + WHIP_BBOX_HEIGHT;
			b.right = b.left + NORMAL_BBOX_WIDTH;
		}
		else
		{
			b.left = position.x + 32.0f;
			b.top = position.y + 6.0f;
			b.bottom = b.top + WHIP_BBOX_HEIGHT;
			b.right = b.left + NORMAL_BBOX_WIDTH;
		}
		break;

	default:
		if (this->direction.x == -1)
		{
			b.left = position.x;
			b.top = position.y + 6.0f;
			b.bottom = b.top + WHIP_BBOX_HEIGHT;
			b.right = b.left + SPECIAL_BBOX_WIDTH;
		}
		else
		{
			b.left = position.x + 32;
			b.top = position.y + 6.0f;
			b.bottom = b.top + WHIP_BBOX_HEIGHT;
			b.right = b.left + SPECIAL_BBOX_WIDTH;
		}
		break;
	}

	return b;
}

void Whip::Render(ViewPort * camera)
{
	int ani;
	switch (type)
	{
	case NORMAL_WHIP:
		if (direction.x == -1)
		{
			ani = 0;
		}
		else if (direction.x == 1)
		{
			ani = 1;
		}
		break;
	case RED_WHIP:
		if (direction.x == -1)
		{
			ani = 2;
		} 
		else if (direction.x == 1)
		{
			ani = 3;
		}
		break;
	case SMALL_WHIP:
		if (direction.x == -1)
		{
			ani = 4;
		}
		else if (direction.x == 1)
		{
			ani = 5;
		}
		break;
	case YELLOW_WHIP:
		if (direction.x == -1)
		{
			ani = 6;
		}
		else if (direction.x == 1)
		{
			ani = 7;
		}
		break;
	case BLUE_WHIP:
		if (direction.x == -1)
		{
			ani = 8;
		}
		else if (direction.x == 1)
		{
			ani = 9;
		}
		break;
	case VIOLET_WHIP:
		if (direction.x == -1)
		{
			ani = 10;
		}
		else if (direction.x == 1)
		{
			ani = 11;
		}
		break;
	}

	D3DXVECTOR3 viewPortPos = this->position;	
	D3DXVECTOR3 bboxPos = viewPortPos;

	CollisionBox b = GetBoundingBox();
	bboxPos.x = b.left;
	bboxPos.y = b.top;

	if (camera != NULL)
	{
		viewPortPos = camera->ConvertPosInViewPort(this->position);
		bboxPos = camera->ConvertPosInViewPort(bboxPos);
	}

	animations[ani]->Render(viewPortPos.x, viewPortPos.y);
	
	RenderBoundingBox(bboxPos.x, bboxPos.y);
}