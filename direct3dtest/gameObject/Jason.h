#pragma once
#include "Player.h"
#define JASON_JUMP_SPEED 0.25
#define JASON_MOVE_ACCEL 0.01
#define JASON_MOVE_SPEED_CAP 0.06

#define BBOX_JASON_WIDTH 8
#define BBOX_JASON_HEIGHT 18

class Jason : public Player {
private:
	bool is_craw = false;
	bool isOnAir = false;
public:
	Jason(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Jason();
	void setCrawState(bool isCraw) { is_craw = isCraw; }
	bool getCrawState() { return is_craw; }
	void changeState(int stateId);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};