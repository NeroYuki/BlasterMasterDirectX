#include "CGame.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManger.h"
#include "scene/DebugScene.h"

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

	_hWnd = CreateWindow(
		"CGame",
		"Begin 3D",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		_scrWidth,
		_scrHeight,
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
	//TODO: attach resources to enemy classes
	TextureManager::getInstance()->add(1, "resource\\Enemies.png", D3DCOLOR_XRGB(255, 0, 255));

	SpriteManager* sprManager = SpriteManager::getInstance();
	LPDIRECT3DTEXTURE9 enemySpriteSheet = TextureManager::getInstance()->get(1);

	//worm move to the right
	sprManager->add(10001, 412, 172, 422, 190, enemySpriteSheet);
	sprManager->add(10002, 412, 191, 422, 212, enemySpriteSheet);
	sprManager->add(20001, 423, 149, 441, 167, enemySpriteSheet);
	sprManager->add(20002, 423, 169, 441, 187, enemySpriteSheet);
	sprManager->add(30001, 145, 131, 163, 149, enemySpriteSheet);
	sprManager->add(30002, 145, 150, 163, 168, enemySpriteSheet);
	

	AnimationManager* aniManager = AnimationManager::getInstance();
	LPANIMATION ani;
	ani = new Animation(100);
	ani->add(10001);
	ani->add(10002);
	LPANIMATION ani2;
	ani2 = new Animation(100);
	ani2->add(20001);
	ani2->add(20002);
	LPANIMATION ani3;
	ani3 = new Animation(100);
	ani3->add(30001);
	ani3->add(30002);

	aniManager->add(101, ani);
	aniManager->add(201, ani2);
	aniManager->add(301, ani3);
	DebugOut("[INFO] All resource sprite loaded\n");
}

void CGame::initGame()
{
	scenePool.push_back(new DebugScene());
	
}

bool CGame::Release()
{
	DebugOut("Program is about to end");
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddev != NULL) d3ddev->Release();
	if (d3d != NULL) d3d->Release();
	return true;
}

void CGame::Loop()
{
	if (d3ddev == NULL) {
		return;
	}
	//d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (d3ddev->BeginScene()) {
		d3ddev->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		//rendering the first most scene
		scenePool[0]->render();
		spriteHandler->End();
		d3ddev->EndScene();
	}

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CGame::draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int top, int left, int bottom, int right)
{
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
