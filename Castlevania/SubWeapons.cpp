#include "SubWeapons.h"
#include "Candles.h"
#include "WalkingGhost.h"


SubWeapons * SubWeapons::_instance = NULL;

SubWeapons * SubWeapons::GetInstance()
{
	if (_instance == NULL) _instance = new SubWeapons();
	return _instance;
}

SubWeapons::SubWeapons()
{
	state = STATE_DIE;
	canDestroy = false;
	direction.x = 1;
	type = -1;
}


SubWeapons::~SubWeapons()
{

}

bool SubWeapons::IsInCameraView(ViewPort * camera)
{
	RECT cameraRegion;
	cameraRegion.left = ViewPort::GetInstance()->GetCameraPos().x;
	cameraRegion.top = ViewPort::GetInstance()->GetCameraPos().y;
	cameraRegion.right = cameraRegion.left + ViewPort::GetInstance()->GetCameraWidth();
	cameraRegion.bottom = cameraRegion.top + ViewPort::GetInstance()->GetCameraHeight();

	if (position.x >= cameraRegion.left &&
		position.x <= cameraRegion.right &&
		position.y >= cameraRegion.top &&
		position.y <= cameraRegion.bottom)
	{
		return true;
	}
	return false;
}

void SubWeapons::SetType(int _type)
{
	type = _type;
	switch (type)
	{
	case SW_KNIFE:
		vy = 0;
		vx = 0.2f;
		break;
	}
}

void SubWeapons::SetPosition(D3DXVECTOR3 _simonPosition, bool isStanding, float direction)
{
	position = _simonPosition;
	this->direction.x = direction;
	switch (type)
	{
	case SW_KNIFE:
		if (isStanding)
		{
			if (this->direction.x == 1)
			{
				position.x = _simonPosition.x + 4;
				position.y = _simonPosition.y + 4;
			}
			else if (this->direction.x == -1)
			{
				position.x = _simonPosition.x + 12;
				position.y = _simonPosition.y + 4;
			}
		}
		else
		{
			if (this->direction.x == 1)
			{
				position.x = _simonPosition.x + 4;
				position.y = _simonPosition.y + 10;
			}
			else if (this->direction.x == -1)
			{
				position.x = _simonPosition.x + 12;
				position.y = _simonPosition.y + 10;
			}
		}
		break;
	}
}

void SubWeapons::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	if (state == STATE_LIVE)
	{
		GameObject::Update(dt, colliableObjects);

		switch (type)
		{
		case SW_KNIFE:
			if (IsInCameraView(ViewPort::GetInstance()) && state == STATE_LIVE)
			{
				position.x += vx * direction.x * dt;

			}
			else
			{
				state = STATE_DIE;
			}
			break;
		}

		HandleCollision(dt, colliableObjects);
	}
}

void SubWeapons::HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{

	vector<LPCOLLISIONEVENT> colliableEvents;
	vector<LPCOLLISIONEVENT> colliableResults;

	colliableEvents.clear(); // Make sure no events remain

	if (state == STATE_LIVE)
		CalPotentialCollision(colliableObjects, colliableEvents);

	if (colliableEvents.size() != 0)
	{
		float min_tx, min_ty, nx, ny;
		FilterCollision(colliableEvents, colliableResults, min_tx, min_ty, nx, ny);

		state = STATE_DIE;

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
					SmallCandles *lc = dynamic_cast<SmallCandles *>(e->GetObj());
					if (lc->GetState() != STATE_DIE)
						lc->SetState(STATE_DIE);
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

void SubWeapons::Render(ViewPort * camera)
{
	D3DXVECTOR3 viewPortPos = camera->ConvertPosInViewPort(this->position);

	switch (type)
	{
	case SW_KNIFE:
		if (direction.x == 1)
		{
			Sprites::GetInstance()->GetSprite(604)->Draw(viewPortPos.x, viewPortPos.y, 255);
		}
		else if (direction.x == -1)
		{
			Sprites::GetInstance()->GetSprite(605)->Draw(viewPortPos.x, viewPortPos.y, 255);
		}
		//RenderBoundingBox(viewPortPos.x, viewPortPos.y);
	}
}


CollisionBox SubWeapons::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	switch (type)
	{
	case SW_KNIFE:
		b.left = position.x;
		b.top = position.y;
		b.right = b.left + 16;
		b.bottom = b.top + 8;
		break;
	}

	return b;
}