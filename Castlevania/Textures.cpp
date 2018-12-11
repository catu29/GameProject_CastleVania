#include "Textures.h"
#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"

Textures * Textures::instance = NULL;

Textures::Textures()
{

}

Textures * Textures::GetInstance()
{
	if (instance == NULL)
	{
		instance = new Textures();
	}
	return instance;
}

LPDIRECT3DTEXTURE9 Textures::GetTexture(unsigned int i)
{
	return texturesList[i];
}

void Textures::Add(int id, LPCSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);

	if (result != D3D_OK)
	{
		OutputDebugString("[ERROR] GetImageFromFile failed\n");
		return;
	}

	LPDIRECT3DDEVICE9 d3ddevice = Graphics::GetInstance()->device;
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddevice,
		filePath,
		info.Width,  
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		&info,
		NULL,
		&texture
	);

	if (result != D3D_OK)
	{
		OutputDebugString("[ERROR] CreateImageFromFile failed\n");
		return;
	}

	texturesList[id] = texture;
	OutputDebugString("[INFO] Texture Loaded OK\n");
}
