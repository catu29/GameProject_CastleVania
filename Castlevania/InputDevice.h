#pragma once
#include <dinput.h>


#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024


class InputDevice
{
private:
	static InputDevice * instance;

	LPDIRECTINPUT8       di;			//direct input object	         
	LPDIRECTINPUTDEVICE8 didv;			//direct input device

	BYTE  keyStates[256];				// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

public:
	InputDevice();
	~InputDevice();

	int IsKeyDown(int keyCode);

	bool Initialize(HWND hWnd);

	void ProcessKeyBoard();

	static InputDevice * GetInstance();
};

typedef InputDevice * LPINPUTDEVICE;

