#include "SceneSection.h"

SceneSection::SceneSection(int top, int left, int bottom, int right) {
	this->top = top;
	this->left = left;
	this->bottom = bottom;
	this->right = right;
}

void SceneSection::getSectionBounding(int& top, int& left, int& bottom, int& right) {
	top = this->top;
	left = this->left;
	bottom = this->bottom;
	right = this->right;
}
