#include "ScenePortal.h"
#pragma once

ScenePortal::ScenePortal(float x, float y, int w, int h, float lx, float ly, int sectionStart, int sectionEnd, int isChangeScene) : Block(x, y, w, h) 
{
	this->lx = lx;
	this->ly = ly;
	this->sectionStart = sectionStart;
	this->sectionEnd = sectionEnd;
}
