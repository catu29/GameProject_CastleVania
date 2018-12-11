#pragma once
#include "Cells.h"
#include "ViewPort.h"

Cells::Cells()
{
	if (cellListObj == NULL)
		cellListObj = new list<LPGAMEOBJECT>;
}

Cells::Cells(D3DXVECTOR2 off)
{
	if (cellListObj == NULL)
		cellListObj = new list<LPGAMEOBJECT>;

	this->offSet = off;
}

Cells::~Cells()
{
}

void Cells::Add(LPGAMEOBJECT obj)
{
	cellListObj->push_back(obj);
}

void Cells::Remove(LPGAMEOBJECT obj)
{
	cellListObj->remove(obj);
}

list<LPGAMEOBJECT>* Cells::GetCellListObjects()
{
	return this->cellListObj;
}


