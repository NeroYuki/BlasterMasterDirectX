#include "InputHandler.h"

InputHandler* InputHandler::__instance = NULL;

InputHandler::InputHandler() {
	
}

void InputHandler::InitKeyboard(LPKEYEVENTHANDLER handler)
{
	//TODO: implement
	HRESULT res = DirectInput8Create((HINSTANCE)GetWindowLong(CGame::getInstance()->getHWnd(), GWL_HINSTANCE), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (res != DI_OK) {
		DebugOut("[ERROR] Initialize DirectInput8 failed\n");
		return;
	}
	res = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (res != DI_OK) {
		DebugOut("[ERROR] Initialize DirectInput8 device failed\n");
		return;
	}
	res = didv->SetDataFormat(&c_dfDIKeyboard);
	res = didv->SetCooperativeLevel(CGame::getInstance()->getHWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	//set buffered device data
	DIPROPDWORD dipr;
	dipr.diph.dwSize = sizeof(DIPROPDWORD);
	dipr.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipr.diph.dwObj = 0;
	dipr.diph.dwHow = DIPH_DEVICE;
	dipr.dwData = KEYBOARD_BUFFER_SIZE;

	res = didv->SetProperty(DIPROP_BUFFERSIZE, &dipr.diph);
	res = didv->Acquire();

	if (res != DI_OK) {
		DebugOut("[ERROR] DINPUT8: Acquire failed\n");
		return;
	}
	this->keyHandler = handler;

	DebugOut("[INFO] Keyboard has been initialized successfully\n");
}

int InputHandler::isKeyDown(int keyCode)
{
	return (keyState[keyCode] & 0x80) > 0;
}

void InputHandler::processKeyboard()
{
	HRESULT res;
	res = didv->GetDeviceState(sizeof(keyState), keyState);
	if (FAILED(res)) {
		if ((res == DIERR_INPUTLOST) || (res == DIERR_NOTACQUIRED))
		{
			HRESULT re_res = didv->Acquire();
			if (re_res == DI_OK)
			{
				DebugOut("[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else {
			return;
		}
	}
	keyHandler->KeyState((BYTE*)this->keyState);
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	res = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvent, &dwElements, 0);
	if (FAILED(res)) {
		return;
	}
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvent[i].dwOfs;
		int KeyState = keyEvent[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

InputHandler* InputHandler::getInstance()
{
	if (__instance == NULL) { __instance = new InputHandler(); }
	return __instance;
}
