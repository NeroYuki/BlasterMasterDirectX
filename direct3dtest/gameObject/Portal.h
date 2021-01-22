#pragma once
#include "Block.h"

class Portal : public Block {
private:
	int sectionStart = 0;
	int sectionEnd = 0;
	float lx = 0, ly = 0;
public:
	Portal(float x, float y, int w, int h, float lx, float ly, int sectionStart, int sectionEnd);
	float getLx() { return lx; }
	float getLy() { return ly; }
	virtual void getHitByBullet() { return; };
	int getSectionStart() { return sectionStart; }
	int getSectionEnd() { return sectionEnd; }
};
