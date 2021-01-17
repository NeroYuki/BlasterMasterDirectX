#pragma once
#include "GameObject.h"
#include "../TextureManager.h"

class Ladder : public GameObject {
private:
	int w = 16, h = 208;
public:
	Ladder(float x, float y, int w, int h);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	void renderBoundingBox();
};