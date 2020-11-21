#include "Portal.h"

Portal::Portal(float x, float y, int w, int h, float lx, float ly, int sectionStart, int sectionEnd) : Block(x, y, w, h){
	this->lx = lx;
	this->ly = ly;
	this->sectionStart = sectionStart;
	this->sectionEnd = sectionEnd;
}