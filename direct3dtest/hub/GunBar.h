#pragma once
#include "../GlobalConstant.h"
#include "../StateDictionary.h"
#include "../gameObject/Player.h"
#include "../Camera.h"


class GunBar {
protected:
	float x = 0, y = 0;
	int state = GUN_BAR_0;
	Player* followingObj = NULL;
	DWORD dt;
	int displayHitPoint = 0;
public:
	void render();
	void update(Camera* cam);
	void setFollow(Player* obj);
	void unfollow();
	int isShow();
};