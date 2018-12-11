#include "Sprites.h"

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
