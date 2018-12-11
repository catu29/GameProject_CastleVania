#pragma once

#include <vector>
#include <d3dx9.h>
#include "Scene.h"
#include "Cells.h"

using namespace std;

class Grid
{
private:

	static Grid * instance;

	vector<vector<Cells *> > listCells;

	float cellWidth;
	float cellHeight;

	float gridWidth;
	float gridHeight;

	int columns;
	int rows;

public:
	Grid();
	~Grid();

	static Grid * GetInstance();

	/*void SetCellWidth(float width) { this->cellWidth = width; }
	void SetCellHeight(float height) { this->cellHeight = height; }*/

	float GetCellWidth() { return this->cellWidth; }
	float GetCellHeight() { return this->cellHeight; }

	float GetGridWidth() { return this->gridWidth; }
	float GetGridHeight() { return this->gridHeight; }

	int GetColumns() { return this->columns; }
	int GetRows() { return this->rows; }

	void Add(D3DXVECTOR2 off, LPGAMEOBJECT obj);
	void Remove(D3DXVECTOR2 off, LPGAMEOBJECT obj);

	void UpdateGrid(TileMap *currentMap);
	void Update(vector<LPGAMEOBJECT>*coliableObjects);

	bool IsExisting(LPGAMEOBJECT obj, int left, int top, int right, int bottom);
};