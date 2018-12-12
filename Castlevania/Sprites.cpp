#include "Sprites.h"
#include <fstream>
#include <sstream>
#include <string.h>

//Structure of Sprite
Sprite::Sprite()
{

}
Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;

	this->sourceRect.left = left;
	this->sourceRect.top = top;
	this->sourceRect.right = right;
	this->sourceRect.bottom = bottom;

	this->texture = tex;
}

void Sprite::Draw(float x, float y, int alpha)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, 0);
	Graphics::GetInstance()->Render(pos, texture, sourceRect, alpha);
}

void Sprite::Draw(float x, float y, RECT rect, int alpha)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, 0);
	Graphics::GetInstance()->Render(pos, texture, rect, alpha);
}

//Manage All Sprite:

Sprites * Sprites::instance = NULL;

Sprites *Sprites::GetInstance()
{
	if (instance == NULL) instance = new Sprites();
	return instance;
}

void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE Sprites::GetSprite(int id)
{
	return sprites[id];
}

void Sprites::LoadDataFromFile(LPCSTR dataPath, LPDIRECT3DTEXTURE9 tex)
{
	fstream pFile;
	pFile.open(dataPath, fstream::in);

	string lineString; // chuoi nam tren dong hien tai
	string subString;
	int value;
	int * posSpace = new int[4]; // luu vi tri cua space vao mot mang
	vector<int> spriteData; // luu left top right bottom

	while (pFile.good())
	{
		getline(pFile, lineString);

		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				posSpace[0] = lineString.find(" ", 0);

				subString = lineString.substr(0, posSpace[0]);

				value = atoi(subString.c_str());

				spriteData.push_back(value);
			}
			else
			{
				posSpace[i] = lineString.find(" ", posSpace[i - 1] + 1);

				subString = lineString.substr(posSpace[i - 1] + 1, posSpace[i] - (posSpace[i - 1] + 1));

				value = atoi(subString.c_str());

				spriteData.push_back(value);
			}
		}
		//add vao sprites
		Add(spriteData[0], spriteData[1], spriteData[2], spriteData[3], spriteData[4], tex);
		spriteData.clear();
	}
}
