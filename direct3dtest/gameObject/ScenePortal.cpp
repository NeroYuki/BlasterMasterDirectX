#include "ScenePortal.h"

ScenePortal::ScenePortal(float x, float y, int w, int h, float lx, float ly, int sectionStart, int sectionEnd, int isChangeScene) : GameObject(x, y)
{
	this->w = w;
	this->h = h;
	this->lx = lx;
	this->ly = ly;
	this->sectionStart = sectionStart;
	this->sectionEnd = sectionEnd;
	this->scenechange = isChangeScene;
}

void ScenePortal::render()
{
}

void ScenePortal::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void ScenePortal::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + h ;
	right = left+w ;
}

void ScenePortal::renderBoundingBox()
{
	(new Sprite(-1, 0, 0, h, w, TextureManager::getInstance()->get(10)))->draw(x, y);
}