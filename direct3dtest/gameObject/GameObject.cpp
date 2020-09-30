#include "GameObject.h"

GameObject::GameObject(float x, float y) {
	this->setPos(x, y);
}

void GameObject::setPos(float x, float y) {
	this->x = x;
	this->y = y;
}
