#pragma once
#include "GlobalConstant.h"
#include "gameObject/GameObject.h"
#include "scene/SceneSection.h"

class Camera
{
private:
	float x = 0, y = 0;
	int w = SCREEN_WIDTH, h = SCREEN_HEIGHT;
	GameObject* followingObj = NULL;
	bool lockX = false; bool lockY = false;
public:
	void update(SceneSection* section);
	void setFollow(GameObject* obj);
	void unfollow();
	void setAxisLock(bool lockX, bool lockY);
	void transform(float x, float y);
	void setPos(float x, float y);
	float getX() { return x; }
	float getY() { return y; }
};

