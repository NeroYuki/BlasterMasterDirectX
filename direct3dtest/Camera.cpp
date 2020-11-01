#include "Camera.h"

void Camera::update()
{
	if (followingObj == NULL) {
		return;
	}
	float obj_x; float obj_y;
	followingObj->getPos(obj_x, obj_y);
	if (!lockX) { this->x = obj_x - (this->w / 2); }
	if (!lockY) { this->y = obj_y - (this->h / 2); }
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
