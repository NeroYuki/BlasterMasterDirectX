#include "Spike.h"

Spike::Spike(float x, float y, int w, int h) : GameObject(x, y)
{
	this->w = w;
	this->h = h;
}

void Spike::render()
{
}

void Spike::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

}

void Spike::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + this->h;
	right = left + this->w;
}

void Spike::renderBoundingBox()
{
	(new Sprite(-1, 0, 0, h, w, TextureManager::getInstance()->get(10)))->draw(x, y);
}
