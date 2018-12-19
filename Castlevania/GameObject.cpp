#include "GameObject.h"
#include "Textures.h"
#include "Grid.h"

GameObject::GameObject()
{
	state = STATE_LIVE;
	canDestroy = false;
	position.x = position.y = 0;
	vx = vy = 0;
}
GameObject::~GameObject()
{

}
void GameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;

	if (state == STATE_DIE)
	{
		if (GetTickCount() - stateTime >= 200)
			canDestroy = true;
	}
}

void GameObject::SetState(int state)
{
	this->state = state;

	if (state == STATE_DIE)
	{
		if (tag == TAG_ITEM || tag == TAG_GATE)
		{
			stateTime = 0;
		}
		else
		{
			stateTime = GetTickCount();
		}

		for (int i = 0; i < cellsOffset.size(); i++)
		{
			Grid::GetInstance()->Remove(cellsOffset[i], this);
		}
	}
	else
	{
		stateTime = GetTickCount();
	}
}

void GameObject::RenderBoundingBox(float x, float y)
{
	RECT rect;

	CollisionBox b = GetBoundingBox();

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)b.right - (int)b.left;
	rect.bottom = (int)b.bottom - (int)b.top;

	Sprites::GetInstance()->Add(25, rect.left, rect.top, rect.right, rect.bottom, Textures::GetInstance()->GetTexture(TEX_BBOX_ID));
	Sprites::GetInstance()->GetSprite(25)->Draw(x, y, 100);
}


/*
This function just checks collision between TWO STATIC object
*/
bool GameObject::AABB(CollisionBox box1, CollisionBox box2)
{
	float left = box2.left - box1.right;
	float top = box2.bottom - box1.top;
	float right = box2.right - box1.left;
	float bottom = box2.top - box1.bottom;

	return !(left > 0 || top < 0 || right < 0 || bottom > 0);
}

/*
This function just checks collision between this object and a STATIC object
*/
void GameObject::SweptAABB(CollisionBox mBox, CollisionBox sBox, float & t, float & nx, float & ny)
{
	float tx_entry, tx_exit, ty_entry, ty_exit;
	float dx_entry, dx_exit, dy_entry, dy_exit;

	float t_entry, t_exit;

	// No collision
	t = -1.0f;
	nx = ny = 0;

	if (AABB(mBox, sBox))
	{
		t = 0;
		nx = -this->direction.x;
		ny = -this->direction.y;
		return;
	}

	//
	// Broad-phase check
	//
	CollisionBox broadBox = mBox; // Box contaning current and next frame
	broadBox.left = this->dx > 0 ? mBox.left : mBox.left + this->dx;
	broadBox.top = this->dy > 0 ? mBox.top : mBox.top + this->dy;
	broadBox.right = this->dx > 0 ? mBox.right + this->dx : mBox.right;
	broadBox.bottom = this->dy > 0 ? mBox.bottom + this->dy : mBox.bottom;


	// Check whether having collision in next frame
	if (broadBox.left > sBox.right || broadBox.top > sBox.bottom || broadBox.right < sBox.left || broadBox.bottom < sBox.top)
		return;

	if (this->dx == 0 && this->dy == 0)
		return; // This object has been idling


	if (this->dx > 0)
	{
		dx_entry = sBox.left - mBox.right;
		dx_exit = sBox.right - mBox.left;
	}
	else if (this->dx < 0)
	{
		dx_entry = sBox.right - mBox.left;
		dx_exit = sBox.left - mBox.right;
	}

	if (this->dy > 0)
	{
		dy_entry = sBox.top - mBox.bottom;
		dy_exit = sBox.bottom - mBox.top;
	}
	else if (this->dy < 0)
	{
		dy_entry = sBox.bottom - mBox.top;
		dy_exit = sBox.top - mBox.bottom;
	}


	if (this->dx == 0)
	{
		tx_entry = -std::numeric_limits<float>::infinity();
		tx_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tx_entry = dx_entry / this->dx;
		tx_exit = dx_exit / this->dx;
	}

	if (this->dy == 0)
	{
		ty_entry = -std::numeric_limits<float>::infinity();
		ty_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		ty_entry = dy_entry / this->dy;
		ty_exit = dy_exit / this->dy;
	}

	// Check conditions whether colliding
	if ((ty_entry < 0 && tx_entry < 0) || tx_entry > 1 || ty_entry > 1)
		return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit)
		return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0;
		nx = this->dx > 0 ? -1.0f : 1.0f;
	}
	else if (ty_entry > tx_entry)
	{
		nx = 0;
		ny = this->dy > 0 ? -1.0f : 1.0f;
	}
	else
	{
		nx = this->dx > 0 ? -1.0f : 1.0f;
		ny = this->dy > 0 ? -1.0f : 1.0f;
	}
}


/*
This function just checks collision between this object and a MOVING object
*/
LPCOLLISIONEVENT GameObject::SweptAABBEx(LPGAMEOBJECT colliableObject)
{
	float time;
	float nx, ny;

	float svx, svy; // Velocity of coliable object
	colliableObject->GetSpeed(svx, svy);

	// Store dx, dy in case they can be changed
	float _dx = this->dx;
	float _dy = this->dy;

	// Relative distance of this to coliable object
	this->dx = _dx - (svx * dt);
	this->dy = _dy - (svy * dt);

	CollisionBox thisBox = this->GetBoundingBox();

	CollisionBox coBox = colliableObject->GetBoundingBox();

	SweptAABB(thisBox, coBox, time, nx, ny);

	this->dx = _dx;
	this->dy = _dy;

	LPCOLLISIONEVENT e = new CollisionEvent(time, nx, ny, colliableObject);
	return e;
}

void GameObject::FilterCollision(vector<LPCOLLISIONEVENT>&colliableEvents, vector<LPCOLLISIONEVENT>&colliableResult, float &min_tx, float &min_ty, float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	colliableResult.clear();

	for (UINT i = 0; i < colliableEvents.size(); i++)
	{
		if (colliableEvents[i]->Get_t() < min_tx && colliableEvents[i]->Get_nx() != 0)
		{
			min_tx = colliableEvents[i]->Get_t();
			nx = colliableEvents[i]->Get_nx();
			min_ix = i;
		}

		if (colliableEvents[i]->Get_t() < min_ty && colliableEvents[i]->Get_ny() != 0)
		{
			min_ty = colliableEvents[i]->Get_t();
			ny = colliableEvents[i]->Get_ny();
			min_iy = i;
		}
	}

	if (min_ix > -1) 
		colliableResult.push_back(colliableEvents[min_ix]);
	if (min_iy > -1) 
		colliableResult.push_back(colliableEvents[min_iy]);
}

void GameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = Animations::GetInstance()->GetAnimation(aniId);
	animations.push_back(ani);
}

