#include "Graphics.h"

Graphics * Graphics::__instance = NULL;

Graphics * Graphics::GetInstance()
{
	if (__instance == NULL) __instance = new Graphics();
	return __instance;
}

Graphics::Graphics()
{
}


Graphics::~Graphics()
{
	if (device)
	{
		device->Release();
		device = NULL;
	}
	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}
}

bool Graphics::Initialize(HWND hWnd, bool  windowed)
{
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS presentationParams;
	ZeroMemory(&presentationParams, sizeof(presentationParams));

	presentationParams.Windowed = windowed;
	presentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParams.BackBufferFormat = D3DFMT_X8R8G8B8;
	presentationParams.BackBufferCount = 1;
	presentationParams.hDeviceWindow = hWnd;

	RECT userRect;
	GetClientRect(hWnd, &userRect);

	presentationParams.BackBufferHeight = userRect.bottom + 1;
	presentationParams.BackBufferWidth = userRect.right + 1;

	D3DCAPS9 caps;
	DWORD behavior;
	HRESULT result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, &caps);

	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		// Use software-only processing
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		// Use hardware-only processing
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, //Adapter mac dinh
		D3DDEVTYPE_HAL, //Device Type: High Speed Graphic Card
		hWnd,
		behavior,
		&presentationParams,
		&device)))
	{
		return false;
	}

	device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	D3DXCreateSprite(device, &spriteHandler);

	return true;
}

void Graphics::Clear(D3DCOLOR color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void Graphics::Render(D3DXVECTOR3 position, LPDIRECT3DTEXTURE9 texture, RECT rect, int alpha)
{
	if (spriteHandler)
	{
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		spriteHandler->Draw(texture, &rect, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));

		spriteHandler->End();
	}
}

bool Graphics::Begin()
{
	return device->BeginScene();
}

void Graphics::End()
{
	device->EndScene();
}

void Graphics::Present()
{
	device->Present(NULL, NULL, NULL, NULL);
}
