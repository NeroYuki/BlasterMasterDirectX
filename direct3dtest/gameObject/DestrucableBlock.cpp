#include "DestrucableBlock.h"

DestrucableBlock::DestrucableBlock(float x, float y, int w, int h) : Block(x, y, w, h)
{
	this->lx = lx;
	this->ly = ly;

}

void DestrucableBlock::render()
{
	LPANIMATION ani; 
	ani = AnimationManager::getInstance()->get(10000000);
	ani->render(x, y);
}

void DestrucableBlock::getHitByBullet()
{
	int randomdrop;
	Collectable* collectable = NULL;
	randomdrop = SharedData::getInstance()->getRandomNumber();
	randomdrop = randomdrop % 6 + 1;
	CollectableManager::getinstance();
	switch (randomdrop) {
	case 1:collectable = new Collectable(this->x, this->y, 1, 3); break;
	case 2:collectable = new Collectable(this->x, this->y, 1, 3); break;
	case 3:collectable = new Collectable(this->x, this->y, 2, 1); break;
	case 4:collectable = new Collectable(this->x, this->y, 2, 1); break;
	default: break;
	}
	if (collectable != NULL)  CollectableManager::getinstance()->addCollectable(collectable);
	this->isDie = 1;
}
