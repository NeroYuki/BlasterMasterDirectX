#include "Enemy.h"

Enemy::Enemy(float x, float y, int hp) : GameObject(x, y){
	this->HitPoint = hp;
}

Enemy::~Enemy()
{
}
