#pragma once
#include "GameObject.h"
#include "../TextureManager.h"

class ScenePortal : public GameObject {
private:
	int sectionStart = 0;
	int sectionEnd = 0;
	float lx = 0, ly = 0;
	int scenechange = 0;
	int w = 16, h = 16;
public:
	ScenePortal(float x, float y, int w, int h, float lx, float ly, int sectionStart, int sectionEnd,int isChangeScene);
	float getLx() { return lx; }
	float getLy() { return ly; }
	int getSectionStart() { return sectionStart; }
	int getSectionEnd() { return sectionEnd; }
	int getIsChangeScene() { return scenechange;}
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	void renderBoundingBox();
};
