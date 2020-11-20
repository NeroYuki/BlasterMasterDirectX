#include "Player.h"
#include <string>

Player::Player(float x, float y, int hp) : GameObject(x,y)
{
	vx = 0; vy = 0;
	sectionSwitchingTimer = new GameTimer(3000);
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
	this->state = stateId;
}
