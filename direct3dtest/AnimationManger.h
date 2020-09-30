#pragma once
#include "SpriteManager.h"

class AnimationFrame
{
private:
	LPSPRITE sprite;
	DWORD time;
public:
	AnimationFrame(LPSPRITE sprite, DWORD time) { this->sprite = sprite; this->time = time; }
	LPSPRITE getSprite() { return this->sprite; }
	DWORD getTime() { return this->time; }
};

typedef AnimationFrame* LPANIMATION_FRAME;

class Animation
{
private:
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	std::vector<LPANIMATION_FRAME> frames;
public:
	Animation(int defaultTime);
	void add(int spriteId, DWORD time = 0);
	void render(float x, float y);
};

typedef Animation* LPANIMATION;

class AnimationManager
{
private:
	static AnimationManager* __instance;
	std::unordered_map<int, LPANIMATION> animations;
	AnimationManager();
public:

	void add(int id, LPANIMATION animation);
	LPANIMATION get(int id);
	static AnimationManager* getInstance();
};

