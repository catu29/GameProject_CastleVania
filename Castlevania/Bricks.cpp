#include "Bricks.h"
#include "Grid.h"


Brick::Brick(int type)
{
	vx = vy = 0;
	direction = D3DXVECTOR2(0, 0);
	this->type = type;
	isStatic = true;
	tag = TAG_BRICK;
	state = STATE_LIVE;
	specialItemType = -1; // There is no special item in default
}


Brick::~Brick()
{
}

/*
Calculate which cells it is living on
*/
void Brick::SetCellsOffSet(float cellWidth, float cellHeight)
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
void Brick::UpdateCells()
{
	// If object has not moved, stop checking
	if (this->dx == 0 && this->dy == 0)
		return;

	vector<D3DXVECTOR2> oldList(cellsOffset); // Store old values to remove from old cells

	SetCellsOffSet(Grid::GetInstance()->GetCellWidth(), Grid::GetInstance()->GetCellHeight());

	for (UINT i = 0; i < oldList.size(); i++)
	{
		Grid::GetInstance()->Remove(oldList[i], this);
	}

	oldList.clear();
}

void Brick::Update(DWORD dt, vector<LPGAMEOBJECT> *colliableObjects)
{
	GameObject::Update(dt, colliableObjects);
	UpdateCells();
}

void Brick::Render(ViewPort * camera)
{
	D3DXVECTOR3 v(0, 0, 0);
	CollisionBox b = this->GetBoundingBox();

	v.x = b.left;
	v.y = b.top;

	v = camera->ConvertPosInViewPort(this->position);

	RenderBoundingBox(v.x, v.y);
}

CollisionBox Brick::GetBoundingBox()
{
	CollisionBox b(0, 0, 0, 0);

	b.left = position.x;
	b.top = position.y;
	b.right = b.left + 16;
	b.bottom = b.top + 16;

	return b;
}

