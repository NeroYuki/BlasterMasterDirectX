#include "HeatlhBar.h"

void HeatlhBar::render()
{
		LPANIMATION ani;

		ani = AnimationManager::getInstance()->get(state);
		ani->render(x, y);
}

void HeatlhBar::update(Camera* cam)
{
	if (followingObj == NULL) {
		return;
	}
	this->x=cam->getX()+10;
	this->y = cam->getY()+100;

	followingObj->GetPlayerHitPoint(displayHitPoint);
	switch (displayHitPoint)
	{
	case 0:state = HIT_POINT_BAR_0; break;
	case 1:state = HIT_POINT_BAR_1; break;
	case 2:state = HIT_POINT_BAR_2; break;
	case 3:state = HIT_POINT_BAR_3; break;
	case 4:state = HIT_POINT_BAR_4; break;
	case 5:state = HIT_POINT_BAR_5; break;
	case 6:state = HIT_POINT_BAR_6; break;
	case 7:state = HIT_POINT_BAR_7; break;
	case 8:state = HIT_POINT_BAR_8; break;
	default:
		state = HIT_POINT_BAR_0; break;
	}
}

void HeatlhBar::setFollow(Player* obj)
{
	this->followingObj = obj;

}

void HeatlhBar::unfollow()
{
	this->followingObj = NULL;
}
