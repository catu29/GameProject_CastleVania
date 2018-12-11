#pragma once
#include <d3dx9.h>



class ViewPort
{
private:
	static ViewPort *instance;
	D3DXVECTOR3 cameraPos;
	
	int cameraWidth, cameraHeight;

	RECT region;
public:
	ViewPort();
	~ViewPort();

	static ViewPort * GetInstance();
	D3DXVECTOR3 ConvertPosInViewPort(D3DXVECTOR3 _realPos);

	void SetCameraPos(D3DXVECTOR3 _camPos);

	void SetCameraSize(int _width, int _height) { cameraWidth = _width; cameraHeight = _height; }

	int GetCameraWidth() { return cameraWidth; }
	int GetCameraHeight() { return cameraHeight; }

	D3DXVECTOR3 GetCameraPos() { return this->cameraPos; }

};

