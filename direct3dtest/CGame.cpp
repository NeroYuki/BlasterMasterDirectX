#include "CGame.h"
#define round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

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

	if (FAILED(result)) return true;

	return true;
}

void CGame::loadResource()
{
	//TODO: EVERYTHING INTO RESOURCE FILE
	TextureManager::getInstance()->add(1, "resource\\Enemies.png", D3DCOLOR_XRGB(0, 255, 0));
	TextureManager::getInstance()->add(2, "resource\\Player.png", D3DCOLOR_XRGB(0, 57, 115));
	TextureManager::getInstance()->add(3, "resource\\OverworldTileset.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(4, "resource\\DungeonTileset.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(5, "resource\\OverworldMapBg.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(6, "resource\\DungeonMapBg.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(8, "resource\\DungeonMapFg.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(9, "resource\\DungeonMapLayoutFg.png", D3DCOLOR_XRGB(255, 0, 255));
	TextureManager::getInstance()->add(10, "resource\\bbox.png", D3DCOLOR_XRGB(255, 0, 255));
	SpriteManager* sprManager = SpriteManager::getInstance();
	
	AnimationManager* aniManager = AnimationManager::getInstance();

	ResourceImporter::spriteImport("resource\\spriteResource.grc", sprManager, aniManager);

	DebugOut("[INFO] All resource sprite loaded\n");
}

void CGame::initGame()
{
	int DebugSceneId = sceneStateMachine->addScene(new DebugScene(sceneStateMachine));
	ResourceImporter::mapDataImport("resource\\map_data\\dungeon_layoutData.csv", sceneStateMachine->getSceneById(DebugSceneId));
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

	if (d3ddev->BeginScene() == D3D_OK) {
		int bgTexture_id = sceneStateMachine->getBgTextureId();
		int fgTexture_id = sceneStateMachine->getFgTextureId();
		Camera* activeCamera = sceneStateMachine->getActiveCamera();
		float transX = activeCamera->getX();
		float transY = activeCamera->getY();

		int transXrounded = round(transX);
		int transYrounded = round(transY);
		
		d3ddev->ColorFill(backBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMATRIX translationMat;
		D3DXMatrixTranslation(&translationMat, -transX, -transY, 0);
		spriteHandler->SetTransform(&translationMat);
		if (bgTexture_id != 0) {
			LPDIRECT3DTEXTURE9 bg_tex = TextureManager::getInstance()->get(bgTexture_id);
			draw(transX, transY, bg_tex, transYrounded, transXrounded, transYrounded + SCREEN_HEIGHT, transXrounded + SCREEN_WIDTH);
		}
		
		sceneStateMachine->render();
		if (fgTexture_id != 0) {
			LPDIRECT3DTEXTURE9 fg_tex = TextureManager::getInstance()->get(fgTexture_id);
			draw(transX, transY, fg_tex, transYrounded, transXrounded, transYrounded + SCREEN_HEIGHT, transXrounded + SCREEN_WIDTH);
		}

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
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_RGBA(255, 255, 255, 255));
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
		D3DCOLOR_XRGB(255, 0, 255),			// Transparent color
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


