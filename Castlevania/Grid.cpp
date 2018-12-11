#pragma once
#include "Grid.h"


Grid * Grid::instance = NULL;

Grid::Grid()
{
	columns = 2;
	rows = 2;

	cellWidth = ViewPort::GetInstance()->GetCameraWidth() / 2.0f;
	cellHeight = ViewPort::GetInstance()->GetCameraHeight() / 2.0f;

	gridWidth = ViewPort::GetInstance()->GetCameraWidth();
	gridHeight = ViewPort::GetInstance()->GetCameraHeight();
}

Grid::~Grid()
{

}

Grid * Grid::GetInstance()
{
	if (instance == NULL)
		instance = new Grid();
	return instance;
}

/*
This method is to update grid again if current map has changed to another one.
*/
void Grid::UpdateGrid(TileMap *currentMap)
{
	// Refresh old list cells
	listCells.clear();

	gridWidth = currentMap->GetColumns() * currentMap->GetTileWidth();
	gridHeight = currentMap->GetRows() * currentMap->GetTileHeight();

	if ((gridWidth / cellWidth) > (int)(gridWidth / cellWidth))
	{
		columns = (gridWidth / cellWidth) + 1;
	}
	else
	{
		columns = (gridWidth / cellWidth);
	}

	if ((gridHeight / cellHeight) > (int)(gridHeight / cellHeight))
	{
		rows = (gridHeight / cellHeight) + 1;
	}
	else
	{
		rows = (gridHeight / cellHeight);
	}

	for (UINT row = 0; row < rows; row++)
	{
		vector<Cells *> rowCells;
		for (UINT col = 0; col < columns; col++)
		{
			Cells * cells = new Cells(D3DXVECTOR2(row, col));
			rowCells.push_back(cells);
		}
		listCells.push_back(rowCells);
		rowCells.clear();
	}
}


/*
This method is to update area checked for colision following camera position
*/
void Grid::Update(vector<LPGAMEOBJECT> *colliableObjects)
{
	// Position of current view
	float viewLeft = ViewPort::GetInstance()->GetCameraPos().x;
	float viewTop = ViewPort::GetInstance()->GetCameraPos().y;
	float viewRight = viewLeft + ViewPort::GetInstance()->GetCameraWidth();
	float viewBottom = viewTop + ViewPort::GetInstance()->GetCameraHeight();

	// Cells contains current view
	int cellLeft = viewLeft / cellWidth;
	int cellTop = viewTop / cellHeight;
	int cellRight = cellLeft;

	if (((viewRight / cellWidth) - (int)(viewRight / cellWidth)) == 0)
	{
		cellRight = viewRight / cellWidth - 1;
	}
	else
	{
		cellRight = viewRight / cellWidth;
	}

	int cellBottom = cellTop;

	if (((viewBottom / cellHeight) - (int)(viewBottom / cellHeight)) == 0)
	{
		cellBottom = viewBottom / cellHeight - 1;
	}
	else
	{
		cellBottom = viewBottom / cellHeight;
	}

	// Area that needs check out whether having collisions
	cellLeft = cellLeft > 0 ? cellLeft - 1 : cellLeft;
	cellTop = cellTop > 0 ? cellTop - 1 : cellTop;
	cellRight = cellRight < (this->columns - 1) ? cellRight + 1 : cellRight;
	cellBottom = cellBottom < (this->rows - 1) ? cellBottom + 1 : cellBottom;

	//CollisionBox collisionView(viewLeft, viewTop, viewRight, viewBottom);
	colliableObjects->clear();

	// Add objects that is in colliding-area to colliable list objects
	for (UINT row = cellTop; row <= cellBottom; row++)
	{
		for (UINT col = cellLeft; col <= cellRight; col++)
		{
			if (((listCells[row][col]->GetCellListObjects())->size()) != 0)
			{
				list<LPGAMEOBJECT>::iterator it = listCells[row][col]->GetCellListObjects()->begin();

				for (it; it != listCells[row][col]->GetCellListObjects()->end(); it++)
				{
					if (!(IsExisting(*it, cellLeft, cellTop, col, row)))
					{
						colliableObjects->push_back(*it);
					}
				}
			}
		}
	}

}

void Grid::Add(D3DXVECTOR2 off, LPGAMEOBJECT obj)
{
	listCells[off.x][off.y]->Add(obj);
}

void Grid::Remove(D3DXVECTOR2 off, LPGAMEOBJECT obj)
{
	listCells[off.x][off.y]->Remove(obj);
}

bool Grid::IsExisting(LPGAMEOBJECT obj, int left, int top, int right, int bottom)
{
	vector<D3DXVECTOR2> off(obj->GetCellsOffSet());

	for (UINT i = 0; i < off.size(); i++)
	{
		if ((off[i].x >= top && off[i].x < bottom) && (off[i].y >= left && off[i].y < right))
			return true;
	}

	off.clear();

	return false;
}