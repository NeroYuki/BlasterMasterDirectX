#include "GunBar.h"

void GunBar::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void GunBar::update(Camera* cam)
{
	if (followingObj == NULL) {
		return;
	}
	this->x = cam->getX() + 10;
	this->y = cam->getY() + 30;

	followingObj->GetPlayerHitPoint(displayHitPoint);
	switch (displayHitPoint)
	{
	case 0:state = GUN_BAR_0; break;
	case 1:state = GUN_BAR_1; break;
	case 2:state = GUN_BAR_2; break;
	case 3:state = GUN_BAR_3; break;
	case 4:state = GUN_BAR_4; break;
	case 5:state = GUN_BAR_5; break;
	case 6:state = GUN_BAR_6; break;
	case 7:state = GUN_BAR_7; break;
	case 8:state = GUN_BAR_8; break;
	default:
		state = GUN_BAR_0; break;
	}
}

void GunBar::setFollow(Player* obj)
{
	this->followingObj = obj;
}

void GunBar::unfollow()
{
	this->followingObj = NULL;
}
