#include "Item.h"
#include "Bricks.h"
#include "Grid.h"
//#include "SubWeapons.h"

Item::Item(int _type)
{
	tag = TAG_ITEM;
	vx = 0;
	vy = 0.15f;
	direction.y = 1;
	type = _type;
	bornTime = GetTickCount();
	state = STATE_LIVE;
	LoadAnimation();
}
Item::~Item()
{
}

/*
Calculate which cells it is living on
*/
void Item::SetCellsOffSet(float cellWidth, float cellHeight)
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
void Item::UpdateCells()
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

void Item::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);

	if (state == STATE_LIVE)
	{
		if (type == ITEM_MONEY_BAG_1000)
		{
			vy = -0.03f;
			direction.y = -1;
			position.y += dy;

			if (position.y < 130)
				position.y = 130;
		}
		else
		{
			HandleCollision(dt, colliableObjects);
		}

		//destroy when over life time
		if (GetTickCount() - bornTime >= 3000)
			canDestroy = true;

		UpdateCells();
	}
}

void Item::HandleCollision(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	vector<LPCOLLISIONEVENT> colliableEvents;
	colliableEvents.clear();

	CalPotentialCollision(colliableObjects, colliableEvents);

	if (colliableEvents.size() == 0)
	{
		position.y += dy;
	}
	else
	{
		for (UINT i = 0; i < colliableEvents.size(); i++)
		{
			if (dynamic_cast<Item *>(colliableEvents[i]->GetObj()))
			{
				colliableEvents.erase(colliableEvents.begin() + i);
			}
		}

		vector<LPCOLLISIONEVENT> colliableResults;
		float min_tx, min_ty, nx, ny;

		FilterCollision(colliableEvents, colliableResults, min_tx, min_ty, nx, ny);

		position.y += dy * min_ty;

		if (nx != 0)
			vx = 0;
		if (ny != 0)
			vy = 0;

		if (type == ITEM_MONEY_BAG_1000)
		{
			vy = -0.03f;
			direction.y = -1;
			position.y += dy;

			if (position.y < 130)
				position.y = 130;
		}
	}
}

void Item::Render(ViewPort * camera)
{
	D3DXVECTOR3 viewPortPos = camera->ConvertPosInViewPort(this->position);
	switch (type)
	{
	case ITEM_SMALL_HEART:
		Sprites::GetInstance()->GetSprite(800)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_BIG_HEART:
		Sprites::GetInstance()->GetSprite(801)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_WHIP_UPGRADE:
		Sprites::GetInstance()->GetSprite(802)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_POT_ROAST:
		Sprites::GetInstance()->GetSprite(803)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_MONEY_BAG_100:
		Sprites::GetInstance()->GetSprite(804)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_MONEY_BAG_400:
		Sprites::GetInstance()->GetSprite(805)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_MONEY_BAG_700:
		Sprites::GetInstance()->GetSprite(806)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_MONEY_BAG_1000:
		Animations::GetInstance()->GetAnimation(800)->Render(viewPortPos.x, viewPortPos.y);
		break;
	case ITEM_KNIFE:
		Sprites::GetInstance()->GetSprite(604)->Draw(viewPortPos.x, viewPortPos.y);
		break;
	case ITEM_CROSS:
		Sprites::GetInstance()->GetSprite(807)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_INVINCIBILITY_POISION:
		Sprites::GetInstance()->GetSprite(808)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_DOUBLE_SHOT:
		Sprites::GetInstance()->GetSprite(809)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_TRIPLE_SHOT:
		Sprites::GetInstance()->GetSprite(810)->Draw(viewPortPos.x, viewPortPos.y, 255);
		break;
	case ITEM_CRYSTAL_BALL:
		Animations::GetInstance()->GetAnimation(801)->Render(viewPortPos.x, viewPortPos.y);
		break;
	}

	RenderBoundingBox(viewPortPos.x, viewPortPos.y);
}


CollisionBox Item::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	b.left = position.x;
	b.top = position.y;
	switch (type)
	{
	case ITEM_SMALL_HEART:
		b.right = b.left + 8;
		b.bottom = b.top + 8;
		break;
	case ITEM_BIG_HEART:
		b.right = b.left + 12;
		b.bottom = b.top + 10;
		break;
	case ITEM_WHIP_UPGRADE:
		b.right = b.left + 17;
		b.bottom = b.top + 17;
		break;
	case ITEM_KNIFE:
		b.right = b.left + 16;
		b.bottom = b.top + 8;
		break;
	case ITEM_POT_ROAST:
		b.right = b.left + 16;
		b.bottom = b.top + 13;
		break;
	case ITEM_MONEY_BAG_100:
		b.right = b.left + 14;
		b.bottom = b.top + 15;
		break;
	case ITEM_MONEY_BAG_400:
		b.right = b.left + 14;
		b.bottom = b.top + 15;
		break;
	case ITEM_MONEY_BAG_700:
		b.right = b.left + 14;
		b.bottom = b.top + 15;
		break;
	case ITEM_MONEY_BAG_1000:
		b.right = b.left + 14;
		b.bottom = b.top + 15;
		break;
	case ITEM_CROSS:
		b.right = b.left + 16;
		b.bottom = b.top + 18;
		break;
	case ITEM_INVINCIBILITY_POISION:
		b.right = b.left + 13;
		b.bottom = b.top + 16;
		break;
	case ITEM_DOUBLE_SHOT:
		b.right = b.left + 14;
		b.bottom = b.top + 14;
		break;
	case ITEM_TRIPLE_SHOT:
		b.right = b.left + 14;
		b.bottom = b.top + 14;
		break;
	case ITEM_CRYSTAL_BALL:
		b.right = b.left + 14;
		b.bottom = b.top + 16;
		break;
	}

	return b;
}

void Item::LoadAnimation()
{
	AddAnimation(800);
}
