#pragma once
#include "Block.h"

class ScenePortal : public Block {
private:
	int sectionStart = 0;
	int sectionEnd = 0;
	float lx = 0, ly = 0;
public:
	ScenePortal(float x, float y, int w, int h, float lx, float ly, int sectionStart, int sectionEnd,int isChangeScene);
	float getLx() { return lx; }
	float getLy() { return ly; }
	int getSectionStart() { return sectionStart; }
	int getSectionEnd() { return sectionEnd; }
};
