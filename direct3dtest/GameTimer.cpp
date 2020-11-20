#include "GameTimer.h"

GameTimer::GameTimer(long interval)
{
	this->interval = interval;
}

void GameTimer::start()
{
	this->isStart = true;
}

void GameTimer::restart()
{
	this->isStart = true;
	current = 0;
}

void GameTimer::stop()
{
	this->isStart = false;
	current = 0;
}

void GameTimer::pause()
{
	this->isStart = false;
}

bool GameTimer::update(long dt)
{
	if (!isStart) return false;
	current += dt;
	if (current >= interval) {
		current = 0;
		return true;
	}
	return false;
}
