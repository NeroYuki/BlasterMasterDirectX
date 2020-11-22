#include "SpriteManager.h"
#include "CGame.h"

SpriteManager* SpriteManager::__instance = NULL;

SpriteManager::SpriteManager() {

}

SpriteManager* SpriteManager::getInstance()
{
	if (__instance == NULL) {
		__instance = new SpriteManager();
	}
	return __instance;
}

void SpriteManager::add(int id, int top, int left, int bottom, int right, LPDIRECT3DTEXTURE9 texture)
{
	LPSPRITE entry = new Sprite(id, top, left, bottom, right, texture);
	this->sprites[id] = entry;
}

LPSPRITE SpriteManager::get(int id)
{
	return this->sprites[id];
}

Sprite::Sprite(int id, int top, int left, int bottom, int right, LPDIRECT3DTEXTURE9 texture)
{
	this->id = id;
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;
	this->texture = texture;
}

void Sprite::draw(float x, float y, D3DCOLOR col)
{
	if (col != NULL)
		CGame::getInstance()->draw(x, y, this->texture, this->top, this->left, this->bottom, this->right, col);
	else
		CGame::getInstance()->draw(x, y, this->texture, this->top, this->left, this->bottom, this->right);
}
