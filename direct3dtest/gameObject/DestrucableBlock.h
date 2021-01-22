#pragma once
#include "Block.h"
#include "../SharedData.h"
#include "CollectableManager.h"
class DestrucableBlock : public Block {
private:
	float lx = 0, ly = 0;
public:
	DestrucableBlock(float x, float y, int w, int h);
	void render();
	virtual void getHitByBullet();
	float getLx() { return lx; }
	float getLy() { return ly; }
};
