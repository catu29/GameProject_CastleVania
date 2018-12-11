#include "Candles.h"
#include "Textures.h"
#include "Grid.h"


LargeCandles::LargeCandles(int dropItem)
{
	tag = TAG_LARGE_CANDLE;
	LoadAnimation();
	width = 16;
	height = 32;
	stateTime = 200;
	typeDroppedItem = dropItem;
}


LargeCandles::~LargeCandles()
{
}

void LargeCandles::LoadAnimation()
{
	AddAnimation(500);
	AddAnimation(501);
	AddAnimation(502);
}

/*
Calculate which cells it is living on
*/
void LargeCandles::SetCellsOffSet(float cellWidth, float cellHeight)
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

void LargeCandles::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);
}

void LargeCandles::Render(ViewPort * camera)
{
	//just display object inside our camera
	if (position.x >= camera->GetCameraPos().x - width && position.x <= camera->GetCameraPos().x + camera->GetCameraWidth())
	{
		D3DXVECTOR3 viewPortPos = camera->ConvertPosInViewPort(this->position);

		switch (state)
		{
		case STATE_LIVE:
			animations[0]->Render(viewPortPos.x, viewPortPos.y);
			break;
		case STATE_DIE:
			animations[1]->Render(viewPortPos.x, viewPortPos.y + 8);
			animations[2]->Render(viewPortPos.x + 8, viewPortPos.y + 11);
			break;
		}

		RenderBoundingBox(viewPortPos.x, viewPortPos.y);
	}
}

CollisionBox LargeCandles::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	b.left = position.x;
	b.top = position.y;
	b.right = b.left + CANDLE_BBOX_WIDTH;
	b.bottom = b.top + CANDLE_BBOX_HEIGHT;

	return b;
}


//=====================================
// Small Candles

SmallCandles::SmallCandles(int dropItem)
{
	tag = TAG_SMALL_CANDLE;
	LoadAnimation();
	width = 8;
	height = 16;
	typeDroppedItem = dropItem;
}
SmallCandles::~SmallCandles()
{

}

/*
Calculate which cells it is living on
*/
void SmallCandles::SetCellsOffSet(float cellWidth, float cellHeight)
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

void SmallCandles::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);
}

void SmallCandles::Render(ViewPort * camera)
{
	if (position.x >= camera->GetCameraPos().x - width && position.x <= camera->GetCameraPos().x + camera->GetCameraWidth())
	{
		D3DXVECTOR3 viewPortPos = camera->ConvertPosInViewPort(this->position);

		switch (state)
		{
		case STATE_LIVE:
			animations[0]->Render(viewPortPos.x, viewPortPos.y);
			break;
		case STATE_DIE:
			animations[1]->Render(viewPortPos.x, viewPortPos.y + 6);
			animations[2]->Render(viewPortPos.x + 2, viewPortPos.y + 12);
			break;
		}

		//RenderBoundingBox(viewPortPos.x, viewPortPos.y);
	}
}

CollisionBox SmallCandles::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	b.left = position.x;
	b.top = position.y;
	b.right = b.left + width;
	b.bottom = b.top + height;

	return b;
}

void SmallCandles::LoadAnimation()
{
	AddAnimation(503);
	AddAnimation(501);
	AddAnimation(502);
}