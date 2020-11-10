#pragma once

class SceneSection {
private:
	int top = 0, left = 0, bottom = 0, right = 0;
public:
	SceneSection(int top, int left, int bottom, int right);
	void getSectionBounding(int& top, int& left, int& bottom, int& right);
};