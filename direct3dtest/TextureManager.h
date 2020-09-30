#pragma once
#include <d3dx9.h>
#include <unordered_map>

class TextureManager
{
private:
	static TextureManager* __instance;
	std::unordered_map<int, LPDIRECT3DTEXTURE9> textures;
	TextureManager();
public:
	
	void add(int id, LPCSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 get(int id);

	static TextureManager* getInstance();
};

