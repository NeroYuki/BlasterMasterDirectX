#pragma once
class CollectableManager;
#include "GameObject.h"
#include "../SharedData.h"
#include "CollectableManager.h"
class Collectable : public GameObject {
protected:
	int value;
	int type;
	int isPicked = 0;
public:
	Collectable(float x, float y, int type, int value);
	void render() ;
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects) ;
	void GetBoundingBox(float& top, float& left, float& bottom, float& right) ;
	~Collectable();
	void getPicked(int& t, int& v);
};