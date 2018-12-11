#pragma once
#include <list>
#include "GameObject.h"

class Cells
{
private:
	list<LPGAMEOBJECT> *cellListObj = NULL;
	D3DXVECTOR2 offSet;

public:
	Cells();
	Cells(D3DXVECTOR2 off);
	~Cells();

	void Add(LPGAMEOBJECT obj);
	void Remove(LPGAMEOBJECT obj);

	D3DXVECTOR2 GetOffSet() { return this->offSet; }
	void SetOffSet(D3DXVECTOR2 off) { this->offSet = off; }

	list<LPGAMEOBJECT> *GetCellListObjects();
};