#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

class Sprite
{
private:
	int id;
	int top;
	int left;
	int bottom;
	int right;
	LPDIRECT3DTEXTURE9 texture;

public:
	Sprite(int id, int top, int left, int bottom, int right, LPDIRECT3DTEXTURE9 texture);

	void draw(float x, float y, D3DCOLOR col = NULL);
	//LPDIRECT3DTEXTURE9 getTexture() { return texture; }
	//void setTexture(LPDIRECT3DTEXTURE9 tex) { texture = tex; }
};

typedef Sprite* LPSPRITE;

class SpriteManager
{
private:
	static SpriteManager* __instance;
	std::unordered_map<int, LPSPRITE> sprites;
	SpriteManager();
public:
	static SpriteManager* getInstance();
	void add(int id, int top, int left, int bottom, int right, LPDIRECT3DTEXTURE9 texture);
	LPSPRITE get(int id);
};

