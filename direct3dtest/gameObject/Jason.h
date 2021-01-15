#pragma once
#include "Player.h"
#include "Sophia.h"
#define JASON_JUMP_SPEED 0.25
#define JASON_MOVE_ACCEL 0.01
#define JASON_MOVE_SPEED_CAP 0.06

#define BBOX_JASON_WIDTH 8
#define BBOX_JASON_HEIGHT 18

class Jason : public Player {
private:
	bool is_craw = false;
	bool isOnAir = false;
	bool isCloseToSophia = false;
	Player* followingSophia = NULL;
public:
	Jason(float x, float y, int hp, int activeSection = 0);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Jason();
	void setCrawState(bool isCraw) { is_craw = isCraw; }
	bool getCrawState() { return is_craw; }
	void changeState(int stateId);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	bool getIsCloseToSophia() { return isCloseToSophia; }
	void setFollow(Player* followingSophia);
	void unfollow();
};