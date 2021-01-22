#pragma once
#include "GameObject.h"
#include "../TextureManager.h"

class Block : public GameObject {
private:
	int w = 16, h = 16;
public:
	Block(float x, float y, int w, int h);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	virtual void getHitByBullet() { return; };
	void renderBoundingBox();
};