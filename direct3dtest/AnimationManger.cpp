#include "AnimationManger.h"

Animation::Animation(int defaultTime) { 
	this->defaultTime = defaultTime; this->currentFrame = -1; this->lastFrameTime = -1; 
}

void Animation::add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;
	LPSPRITE sprite = SpriteManager::getInstance()->get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::render(float x, float y)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->getTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}

	frames[currentFrame]->getSprite()->draw(x, y);
}

AnimationManager::AnimationManager()
{
}

AnimationManager* AnimationManager::__instance = NULL;

void AnimationManager::add(int id, LPANIMATION animation)
{
	this->animations[id] = animation;
}

LPANIMATION AnimationManager::get(int id)
{
	return this->animations[id];
}

AnimationManager* AnimationManager::getInstance()
{
	if (__instance == NULL) {
		__instance = new AnimationManager();
	}
	return __instance;
}
