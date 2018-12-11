#pragma once
#include "Stairs.h"
#include "Grid.h"

Stair::Stair(int type)
{
	tag = TAG_STAIR;
	this->type = type;
}

Stair::~Stair()
{
}

/*
Calculate which cells it is living on
*/
void Stair::SetCellsOffSet(float cellWidth, float cellHeight)
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

void Stair::Render(ViewPort * camera)
{
	D3DXVECTOR3 p(0, 0, 0);
	CollisionBox b = this->GetBoundingBox();

	p.x = b.left;
	p.y = b.top;

	p = camera->ConvertPosInViewPort(this->position);

	RenderBoundingBox(p.x, p.y);
}

CollisionBox Stair::GetBoundingBox()
{
	return CollisionBox(position.x, position.y, position.x + 16, position.y + 8);
}
