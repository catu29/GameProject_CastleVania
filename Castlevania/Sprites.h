#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Graphics.h"
#include <unordered_map>

using namespace std;

//Stuct Sprite
class Sprite
{
private:
	int						id;				// Sprite ID in the sprite database

	RECT					sourceRect;
	LPDIRECT3DTEXTURE9		texture;
	bool					isFlipHorizontal;
	bool					isFlipVertical;
public:
	Sprite();
	Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255);

	void Draw(float x, float y, RECT rect, int alpha = 255);

	void SetFlipHorizontal(bool flag) { isFlipHorizontal = flag; }
	bool IsFlipHorizontal() { return isFlipHorizontal; }
	void SetFlipVertical(bool flag) { isFlipVertical = flag; }
	bool IsFlipVertical() { return isFlipVertical; }
};

typedef Sprite * LPSPRITE;

//Sprite Manager
class Sprites
{
	static Sprites * instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE GetSprite(int id);

	static Sprites * GetInstance();
};

