#include "TextureManager.h"
#include "CGame.h"

TextureManager* TextureManager::__instance = NULL;

TextureManager::TextureManager()
{
}

void TextureManager::add(int id, LPCSTR filePath, D3DCOLOR transparentColor)
{
	textures[id] = CGame::getInstance()->loadTexture(filePath);
}

LPDIRECT3DTEXTURE9 TextureManager::get(int id)
{
	return textures[id];
}

TextureManager* TextureManager::getInstance()
{
	if (__instance == NULL) {
		__instance = new TextureManager();
	}
	return __instance;
}
