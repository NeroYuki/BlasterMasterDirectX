#include "Block.h"

Block::Block(float x, float y, int w, int h) : GameObject(x, y)
{
	this->w = w;
	this->h = h;
}

void Block::render()
{
}

void Block::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Block::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + this->h;
	right = left + this->w;
}

void Block::renderBoundingBox()
{
	(new Sprite(-1, 0, 0, h, w, TextureManager::getInstance()->get(10)))->draw(x, y);
}
