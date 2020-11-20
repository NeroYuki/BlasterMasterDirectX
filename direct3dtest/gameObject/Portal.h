#pragma once
#include "Block.h"

class Portal : public Block {
private:
	int sectionEnd = 0;
	float lx = 0, ly = 0;
public:
	Portal(float x, float y, int w, int h, float lx, float ly, int sectionEnd);
};
