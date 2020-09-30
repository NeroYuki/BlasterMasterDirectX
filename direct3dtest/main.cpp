#include "CGame.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define FRAME_RATE 30

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAME_RATE;
	CGame::setInstance(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, true, FRAME_RATE);

	CGame::getInstance()->InitWindow();
	CGame::getInstance()->loadResource();
	CGame::getInstance()->initGame();

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
				CGame::getInstance()->Loop();
			}
			else
				Sleep(tickPerFrame - dt);
		}
	}
	CGame::getInstance()->Release();
	return 0;
}