#include "Portal.h"

Portal::Portal(float x, float y, int w, int h, int sectionStart, int sectionEnd) : Block(x, y, w, h){
	this->sectionEnd = sectionEnd;
	this->sectionStart = sectionStart;
}