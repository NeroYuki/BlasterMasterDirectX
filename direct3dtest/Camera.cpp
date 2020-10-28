#include "Camera.h"

void Camera::update()
{
	if (followingObj == NULL) {
		return;
	}
	if (!lockX) { this->x = followingObj->getX() - (this->w / 2); }
	if (!lockY) { this->y = followingObj->getY() - (this->h / 2); }
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
