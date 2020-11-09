#pragma once
#include "Block.h"

class Portal : public Block {
private:
	int sectionStart = 0;
	int sectionEnd = 0;
public:
	Portal(float x, float y, int w, int h, int sectionStart, int sectionEnd);
};
