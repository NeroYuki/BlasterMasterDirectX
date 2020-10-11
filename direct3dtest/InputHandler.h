#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "CGame.h"

#define KEYBOARD_BUFFER_SIZE 1024

class KeyEventHandler
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef KeyEventHandler* LPKEYEVENTHANDLER;

class InputHandler {
private:
	BYTE keyState[256];
	DIDEVICEOBJECTDATA keyEvent[KEYBOARD_BUFFER_SIZE];

	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 didv;

	LPKEYEVENTHANDLER keyHandler;

	static InputHandler* __instance;
	InputHandler();
public:
	void InitKeyboard(LPKEYEVENTHANDLER handler);

	int isKeyDown(int keyCode);
	void processKeyboard();
	static InputHandler* getInstance();
};