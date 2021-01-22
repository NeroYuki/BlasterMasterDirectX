#include "BossJoint.h"
#define PI 3.14159265

BossJoint::BossJoint(float x, float y, float len, float i, int hp) :Enemy(x, y, hp)
{
	this->state = 50004;
	this->x = x;
	this->y = y;
	this->len = len;
	calculateB();
}

BossJoint::BossJoint(BossJoint* b, float len, float i) : Enemy(0, 0, 1)
{
	this->state = 50004;
	b->getEnd(this->x, this->y);
	this->len = len;
	calculateB();
}

void BossJoint::render()
{
	float tempx, tempy;
	tempx = (x + x2) / 2;
	tempy = (y + y2) / 2;
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(tempx-8, tempy-8);
}

void BossJoint::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

}

void BossJoint::update()
{
	calculateB();
}

void BossJoint::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	float tempx, tempy;
	tempx = (x + x2) / 2;
	tempy = (y + y2) / 2;
	top = tempy - 8;
	left = tempx - 8;
	bottom = tempy + 8;
	right = tempx + 8;
}

BossJoint::~BossJoint()
{
}

void BossJoint::calculateB() {
	this->x2 = this->x + len * cos(angle);
	this->y2 = this->y + len * sin(angle);
}

void BossJoint::getEnd(float& x, float& y)
{
	x = this->x2;
	y = this->y2;
}
void  BossJoint :: follow(BossJoint* child) {
	float targetX, targetY; 
	child->getPos(targetX, targetY);
	follow(targetX, targetY); 
}

void  BossJoint :: follow(float tx, float ty) {

	float tempx, tempy,tempc, mul;
	tempx = tx - this->x;
	tempy = ty - this->y;

	this->angle = atan2(tempy, tempx);

	tempc = sqrt(tempx * tempx  +tempy * tempy);
	mul = this->len / tempc;
	tempx = (tempx * mul);
	tempy = (tempy * mul);

	this->x = tx - tempx;
	this->y = ty - tempy;
}

void BossJoint::setState(int i)
{
	if (i == 1) {
		this->state = BOSS_CLAW;
	}
	else if(i ==2)
		this->state = BOSS_RIGHT_CLAW;

}
