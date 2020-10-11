#include "CGame.h"
#include "GlobalConstant.h"
#include "InputHandler.h"


//uh, put it somewhere else?
class SampleKeyHandler : public KeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

SampleKeyHandler* keyHandler;

void SampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut("[INFO] KeyDown: %d\n", KeyCode);
}

void SampleKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut("[INFO] KeyUp: %d\n", KeyCode);
}


void SampleKeyHandler::KeyState(BYTE* states)
{
	if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT)) {}
		//mario->SetState(MARIO_STATE_WALKING_RIGHT);
	if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)) {}
		//mario->SetState(MARIO_STATE_WALKING_LEFT);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAME_RATE;
	CGame::setInstance(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, true, FRAME_RATE);

	CGame::getInstance()->InitWindow();
	CGame::getInstance()->loadResource();
	CGame::getInstance()->initGame();
	keyHandler = new SampleKeyHandler();

	InputHandler::getInstance()->InitKeyboard(keyHandler);

	ZeroMemory(&msg, sizeof(msg));

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				done = 1;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			DWORD now = GetTickCount();

			// dt: the time between (beginning of last frame) and now
			// this frame: the frame we are about to render
			DWORD dt = now - frameStart;

			if (dt >= tickPerFrame)
			{
				frameStart = now;
				InputHandler::getInstance()->processKeyboard();
				CGame::getInstance()->Loop(dt);
			}
			else
				Sleep(tickPerFrame - dt);
		}
	}
	CGame::getInstance()->Release();
	return 0;
}