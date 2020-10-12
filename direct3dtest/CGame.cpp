#include "CGame.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManger.h"

CGame* CGame::__instance = NULL;

LRESULT WINAPI CGame::_WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CGame::InitWindow()
{

	WNDCLASS wndc;
	ZeroMemory(&wndc, sizeof(wndc));

	wndc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndc.hIcon = NULL;
	wndc.hInstance = _hInstance;
	wndc.lpfnWndProc = (WNDPROC)_WinProc;
	wndc.lpszClassName = "CGame";
	wndc.lpszMenuName = NULL;
	wndc.style = NULL;

	if (!RegisterClass(&wndc)) {
		MessageBox(0, "Can not register class", "Error", MB_OK);
		return false;
	}

	RECT wr = { 0, 0, _scrWidth, _scrHeight };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size


	_hWnd = CreateWindow(
		"CGame",
		"Master Blaster Test",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		_hInstance,
		NULL
	);

	if (!_hWnd) {
		MessageBox(0, "Can not create window", "Error", MB_OK);
		return false;
	}

	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d == NULL) {
		MessageBox(_hWnd, "Error initializing Direct3D", "Error", MB_OK);
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	if (d3ddev == NULL) {
		MessageBox(_hWnd, "Error creating Direct3D Device", "Error", MB_OK);
		return false;
	}

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(100, 100, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);

	D3DXCreateSprite(d3ddev, &spriteHandler);

	if (!result) return true;

	return true;
}

void CGame::loadResource()
{
	//TODO: EVERYTHING INTO RESOURCE FILE
	TextureManager::getInstance()->add(1, "resource\\Enemies.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(2, "resource\\Player.png", D3DCOLOR_XRGB(0, 57, 115));

	SpriteManager* sprManager = SpriteManager::getInstance();
	LPDIRECT3DTEXTURE9 enemySpriteSheet = TextureManager::getInstance()->get(1);
	LPDIRECT3DTEXTURE9 playerSpriteSheet = TextureManager::getInstance()->get(2);
	
	sprManager->add(10001, 412, 45, 422, 63, enemySpriteSheet);
	sprManager->add(10002, 412, 64, 422, 82, enemySpriteSheet);
	sprManager->add(10003, 412, 191, 422, 212, enemySpriteSheet);
	sprManager->add(10004, 412, 172, 422, 190, enemySpriteSheet);
	sprManager->add(20001, 145, 44, 165, 64, enemySpriteSheet);
	sprManager->add(20002, 145, 65, 165, 85, enemySpriteSheet);
	sprManager->add(20003, 145, 172, 165, 190, enemySpriteSheet);
	sprManager->add(20004, 145, 193, 165, 211, enemySpriteSheet);
	sprManager->add(30001, 145, 131, 163, 149, enemySpriteSheet);
	sprManager->add(30002, 145, 150, 163, 168, enemySpriteSheet);
	sprManager->add(100001, 4, 209, 36, 233, playerSpriteSheet);
	sprManager->add(100002, 4, 234, 36, 258, playerSpriteSheet);
	sprManager->add(100003, 4, 259, 36, 283, playerSpriteSheet);
	sprManager->add(100011, 37, 209, 69, 233, playerSpriteSheet);
	sprManager->add(100012, 37, 234, 69, 258, playerSpriteSheet);
	sprManager->add(100013, 37, 259, 69, 283, playerSpriteSheet);
	sprManager->add(100021, 70, 209, 102, 233, playerSpriteSheet);
	sprManager->add(100022, 70, 234, 102, 258, playerSpriteSheet);
	sprManager->add(100023, 70, 259, 102, 283, playerSpriteSheet);
	sprManager->add(100031, 70, 284, 102, 308, playerSpriteSheet);
	sprManager->add(100032, 70, 309, 102, 333, playerSpriteSheet);
	sprManager->add(100033, 70, 334, 102, 358, playerSpriteSheet);

	AnimationManager* aniManager = AnimationManager::getInstance();

	LPANIMATION WormMoveLeft = new Animation(100);
	WormMoveLeft->add(10001);
	WormMoveLeft->add(10002);
	LPANIMATION WormMoveRight = new Animation(100);
	WormMoveRight->add(10003);
	WormMoveRight->add(10004);
	LPANIMATION WormIdleLeft = new Animation(100);
	WormIdleLeft->add(10001);
	LPANIMATION WormIdleRight = new Animation(100);
	WormIdleRight->add(10003);
	
	LPANIMATION FloaterMoveLeft = new Animation(100);
	FloaterMoveLeft->add(20001);
	FloaterMoveLeft->add(20002);
	LPANIMATION FloaterMoveRight = new Animation(100);
	FloaterMoveRight->add(20003);
	FloaterMoveRight->add(20004);
	LPANIMATION FloaterIdleLeft = new Animation(100);
	FloaterIdleLeft->add(20001);
	FloaterIdleLeft->add(20002);
	LPANIMATION FloaterIdleRight = new Animation(100);
	FloaterIdleRight->add(20003);
	FloaterIdleRight->add(20004);

	LPANIMATION DomeMoveLeft = new Animation(100);
	DomeMoveLeft->add(30001);
	DomeMoveLeft->add(30002);

	LPANIMATION TopJasonMoveDown = new Animation(100);
	TopJasonMoveDown->add(100001);
	TopJasonMoveDown->add(100002);
	TopJasonMoveDown->add(100003);
	LPANIMATION TopJasonMoveUp = new Animation(100);
	TopJasonMoveUp->add(100011);
	TopJasonMoveUp->add(100012);
	TopJasonMoveUp->add(100013);
	LPANIMATION TopJasonMoveLeft = new Animation(100);
	TopJasonMoveLeft->add(100021);
	TopJasonMoveLeft->add(100022);
	TopJasonMoveLeft->add(100023);
	LPANIMATION TopJasonMoveRight = new Animation(100);
	TopJasonMoveRight->add(100031);
	TopJasonMoveRight->add(100032);
	TopJasonMoveRight->add(100033);
	LPANIMATION TopJasonIdleDown = new Animation(100);
	TopJasonIdleDown->add(100002);
	LPANIMATION TopJasonIdleUp = new Animation(100);
	TopJasonIdleUp->add(100012);
	LPANIMATION TopJasonIdleLeft = new Animation(100);
	TopJasonIdleLeft->add(100022);
	LPANIMATION TopJasonIdleRight = new Animation(100);
	TopJasonIdleRight->add(100032);

	aniManager->add(WORM_MOVE_LEFT, WormMoveLeft);
	aniManager->add(WORM_MOVE_RIGHT, WormMoveRight);
	aniManager->add(WORM_IDLE_LEFT, WormIdleLeft);
	aniManager->add(WORM_IDLE_RIGHT, WormIdleRight);
	aniManager->add(FLOATER_MOVE_LEFT, FloaterMoveLeft);
	aniManager->add(FLOATER_MOVE_RIGHT, FloaterMoveRight);
	aniManager->add(FLOATER_IDLE_LEFT, FloaterIdleLeft);
	aniManager->add(FLOATER_IDLE_RIGHT, FloaterIdleRight);
	aniManager->add(DOME_MOVE_LEFT, DomeMoveLeft);

	aniManager->add(TOP_JASON_WALK_DOWN, TopJasonMoveDown);
	aniManager->add(TOP_JASON_WALK_UP, TopJasonMoveUp);
	aniManager->add(TOP_JASON_WALK_LEFT, TopJasonMoveLeft);
	aniManager->add(TOP_JASON_WALK_RIGHT, TopJasonMoveRight);
	aniManager->add(TOP_JASON_IDLE_DOWN, TopJasonIdleDown);
	aniManager->add(TOP_JASON_IDLE_UP, TopJasonIdleUp);
	aniManager->add(TOP_JASON_IDLE_LEFT, TopJasonIdleLeft);
	aniManager->add(TOP_JASON_IDLE_RIGHT, TopJasonIdleRight);

	DebugOut("[INFO] All resource sprite loaded\n");
}

void CGame::initGame()
{
	int DebugSceneId = sceneStateMachine->addScene(new DebugScene(sceneStateMachine));
	sceneStateMachine->switchToScene(DebugSceneId);
}

bool CGame::Release()
{
	DebugOut("[INFO] Program is about to end\n");
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddev != NULL) d3ddev->Release();
	if (d3d != NULL) d3d->Release();
	return true;
}

void CGame::Loop(DWORD dt)
{
	if (d3ddev == NULL) {
		return;
	}
	//d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	sceneStateMachine->handlingInput();
	sceneStateMachine->update(dt);

	if (d3ddev->BeginScene()) {
		d3ddev->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		sceneStateMachine->render();
		spriteHandler->End();
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CGame::draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int top, int left, int bottom, int right)
{
	//D3DXMATRIX scaleMat;
	//D3DXMatrixScaling(&scaleMat, 2.0, 1.0, 1.0);
	//
	//spriteHandler->SetTransform(&scaleMat);

	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}

LPDIRECT3DTEXTURE9 CGame::loadTexture(LPCSTR texturePath)
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;
	HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);

	if (result != D3D_OK)
	{
		return NULL;
	}

	result = D3DXCreateTextureFromFileEx(
		d3ddev,								// Pointer to Direct3D device object
		texturePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		return NULL;
	}

	return texture;
}

CGame::CGame(HINSTANCE hInstance, int screenWidth, int screenHeight, bool something, int frameRate)
{
	_hInstance = hInstance;
	_scrWidth = screenWidth;
	_scrHeight = screenHeight;
	_frameRate = frameRate;
	sceneStateMachine = new SceneStateMachine();
}

CGame::~CGame()
{

}

void CGame::setInstance(HINSTANCE hInstance, int screenWidth, int screenHeight, bool something, int frameRate) {
	if (__instance != NULL) {
		__instance->Release();
		delete __instance;
		__instance = NULL;
	}
	__instance = new CGame(hInstance, screenWidth, screenHeight, something, frameRate);
}

CGame* CGame::getInstance() {
	if (__instance == NULL) {
		return NULL;
	}
	return __instance;
}
