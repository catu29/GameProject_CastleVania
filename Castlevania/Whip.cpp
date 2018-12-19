
#include "Whip.h"
#include "Animations.h"
#include "Textures.h"

Whip::Whip()
{
	LoadAnimation();	
	state = 0;
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
	AddAnimation(102); // 2 animation lightning star left
	AddAnimation(103); // 3 animation lightning star right
	AddAnimation(104); // 4 animation vampire killer left
	AddAnimation(105); // 5 animation vampire killer right
}

void Whip::SetPosition(D3DXVECTOR3 _simonPosition, bool _isStanding, float dir)
{
	this->direction.x = dir;
	switch (type)
	{
	case NORMAL_WHIP: case LIGHTNING_STAR_WHIP:
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
	case VAMPIRE_KILLER_WHIP:
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

void Whip::CalPotentialCollision(vector<LPGAMEOBJECT>* colliableObjects, vector<LPCOLLISIONEVENT>& colliableEvents)
{
	for (UINT i = 0; i < colliableObjects->size(); i++)
	{
		if (colliableObjects->at(i)->GetTag() == TAG_ITEM || colliableObjects->at(i)->GetTag() == TAG_STAIR)
		{
			continue;
		}
		else
		{
			CollisionBox b1 = this->GetBoundingBox();
			CollisionBox b2 = colliableObjects->at(i)->GetBoundingBox();

			if (AABB(b1, b2))
			{
				LPCOLLISIONEVENT e = new CollisionEvent(0, -this->direction.x, -this->direction.y, colliableObjects->at(i));
				colliableEvents.push_back(e);
			}
		}
	}

	std::sort(colliableEvents.begin(), colliableEvents.end());
}

void Whip::HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);

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

			else if (e->GetObj()->GetTag() == TAG_SMALL_CANDLE)
			{
				if (dynamic_cast<SmallCandles *>(e->GetObj()))
				{
					SmallCandles *sc = dynamic_cast<SmallCandles *>(e->GetObj());
					if (sc->GetState() != STATE_DIE)
						sc->SetState(STATE_DIE);
				}
			}

			else if (e->GetObj()->GetTag() == TAG_WALKING_GHOST)
			{
				if (dynamic_cast<WalkingGhost *>(e->GetObj()))
				{
					WalkingGhost *wg = dynamic_cast<WalkingGhost *>(e->GetObj());
					if (wg->GetState() != STATE_DIE)
						wg->SetState(STATE_DIE);
				}
			}
		}
	}
}

CollisionBox Whip::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	switch (type)
	{
	case NORMAL_WHIP:
	case LIGHTNING_STAR_WHIP:
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
	case LIGHTNING_STAR_WHIP:
		if (direction.x == -1)
		{
			ani = 2;
		}
		else if (direction.x == 1)
		{
			ani = 3;
		}
		break;
	case VAMPIRE_KILLER_WHIP:
		if (direction.x == -1)
		{
			ani = 4;
		}
		else if (direction.x == 1)
		{
			ani = 5;
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