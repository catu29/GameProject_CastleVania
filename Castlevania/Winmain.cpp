#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Define.h"


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

bool CreateGameWindow(HWND & hWnd, HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;
		
	if (RegisterClassEx(&wc) == 0)
	{
		return false;
	}

	hWnd = CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString("[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return false;
	}
	if (!FULLSCREEN)
	{
		RECT rectClient;
		GetClientRect(hWnd, &rectClient);
		MoveWindow(hWnd, 200, 50, SCREEN_WIDTH + (SCREEN_WIDTH - rectClient.right -1), SCREEN_HEIGHT + (SCREEN_HEIGHT - rectClient.bottom -1), TRUE);
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	
	if (CreateGameWindow(hWnd, hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		if (!Game::GetInstance()->Initialize(hWnd))
		{
			OutputDebugString("[GAME] Init not succeed");
			return 0;
		}

		

		SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

		Game::GetInstance()->Run();
	}
	return 0;
}