#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "../AnimationManger.h"

class GameObject {
protected:
	float x, y;		//position, should be a new class (CPoint?)
public:
	//constructor
	GameObject(float x, float y);

	void setPos(float x, float y);
	float getX() { return x; }
	float getY() { return y; }
	
	virtual void update(DWORD dt) = 0;
	virtual void render() = 0;
};