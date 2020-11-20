#include "Camera.h"

void Camera::update(SceneSection* section)
{
	if (followingObj == NULL) {
		return;
	}
	float obj_x; float obj_y;
	int bt, bl, bb, br;

	followingObj->getPos(obj_x, obj_y);

	//check if planned movement blocked by section bounding
	int initX = obj_x - (this->w / 2);
	int initY = obj_y - (this->h / 2);

	if (section == nullptr) {
		this->x = initX;
		this->y = initY;
		return;
	}

	section->getSectionBounding(bt, bl, bb, br);

	if (initX <= bl) this->x = bl;
	else if (initX + this->w >= br) this->x = br - this->w;
	else this->x = initX;
	if (initY <= bt) this->y = bt;
	else if (initY + this->h >= bb) this->y = bb - this->h;
	else this->y = initY;
}

void Camera::setFollow(GameObject* obj)
{
	this->followingObj = obj;
}

void Camera::unfollow()
{
	this->followingObj = NULL;
}

void Camera::setAxisLock(bool lockX, bool lockY)
{
	this->lockX = lockX;
	this->lockY = lockY;
}

void Camera::transform(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Camera::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}
