#include "Player.h"
#include <string>

Player::Player(float x, float y, int hp) : GameObject(x,y)
{
	vx = 0; vy = 0;
}

void Player::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Player::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

}

Player::~Player()
{
}

void Player::changeState(int stateId)
{
}

//NOTE: Turn to pure virtual ASAP after inheiritance is completed
void Player::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{

}
