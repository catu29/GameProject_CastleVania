#include "InputDevice.h"
#include "SceneManager.h"

InputDevice * InputDevice::instance = NULL;


InputDevice::InputDevice()
{
}


InputDevice::~InputDevice()
{
}

InputDevice * InputDevice::GetInstance()
{
	if (instance == NULL) instance = new InputDevice();
	return instance;
}

int InputDevice::IsKeyDown(int keyCode)
{
	return (keyStates[keyCode] & 0x80) > 0;
}


bool InputDevice::Initialize(HWND hWnd)
{
	// 1 - create a direct input object
	HRESULT hr = DirectInput8Create(
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&di,
		NULL
	);
	if (hr != DI_OK)
	{
		return false;
	}
	// 2 - create a direct input device
	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	if (hr != DI_OK)
	{
		return false;
	}

	// 3 - Set data format - device sent to object
	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	// 4 - Set cooperative lvl - work with system - windowed state
	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; 

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph); // ? 


	// 5 - ready to read data from device
	hr = didv->Acquire();

	if (hr != DI_OK)
	{
		return false;
	}

	return true;
}



void InputDevice::ProcessKeyBoard()
{
	HRESULT hr;

	// Collect all key states first
	// Check pressed key
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == !DI_OK)
			{
				return;
			}
		}
		else
		{
			return;
		}
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		return;
	}



	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
 		if ((KeyState & 0x80) > 0)
		{
			SceneManager::GetInstance()->GetCurrentScene()->OnKeyDown(KeyCode);
		}
		else
		{
			SceneManager::GetInstance()->GetCurrentScene()->OnKeyUp(KeyCode);
		}
	}

	SceneManager::GetInstance()->GetCurrentScene()->KeyState();
}
