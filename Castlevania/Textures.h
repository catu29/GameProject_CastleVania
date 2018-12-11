#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

//Manage Textures database
class Textures
{
private:
	static Textures * instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> texturesList;

public:
	Textures();
	void Add(int id, LPCSTR filePath, D3DCOLOR transparentcolor);
	LPDIRECT3DTEXTURE9 GetTexture(unsigned int i);

	static Textures * GetInstance();

};

