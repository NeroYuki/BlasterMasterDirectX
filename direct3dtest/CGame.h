#pragma once
#include <Windows.h>
#include <vector>
#include "d3d9.h"
#include "d3dx9.h"
#include "Debug.h"
#include "SceneStateMachine.h"
#include "scene/DebugScene.h"
#include "scene/OverworldScene.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "AnimationManger.h"
#include "ResourceImporter.h"

class CGame
{
private:

	static CGame* __instance;
	HWND _hWnd;
	HINSTANCE _hInstance;
	static LRESULT WINAPI _WinProc(HWND, UINT, WPARAM, LPARAM);
	int _scrWidth;
	int _scrHeight;
	int _frameRate;

	SceneStateMachine* sceneStateMachine;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddev = NULL;

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPDIRECT3DSURFACE9 surface = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

	CGame(HINSTANCE hInstance, int screenWidth, int screenHeight, bool something, int frameRate);

public:
	
	~CGame();
	static void setInstance(HINSTANCE hInstance, int screenWidth, int screenHeight, bool something, int frameRate);
	static CGame* getInstance();
	bool InitWindow();
	void loadResource();
	void initGame();
	bool Release();
	void Loop(DWORD dt);
	void draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int top, int left, int bottom, int right, D3DCOLOR col = NULL);
	//void drawWithTransform(float x, float y, LPDIRECT3DTEXTURE9 texture, int top, int left, int bottom, int right, float translateX, float translateY);
	

	LPDIRECT3DTEXTURE9 loadTexture(LPCSTR texturePath);

	HWND getHWnd() { return _hWnd; }
};

