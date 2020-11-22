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

//state 0 = inactive, 1 = started, 2 = active, 3 = ended
short GameTimer::update(long dt)
{
	if (!isStart) return TIMER_INACTIVE;
	current += dt;
	if (current == dt) {
		return TIMER_STARTED;
	}
	if (current < interval) {
		return TIMER_ACTIVE;
	}
	else {
		this->stop();
		return TIMER_ENDED;
	}
}

short GameTimer::peekState()
{
	if (!isStart) return TIMER_INACTIVE;
	if (current == 0) return TIMER_STARTED;
	if (current < interval) {
		return TIMER_ACTIVE;
	}
	else {
		return TIMER_ENDED;
	}
}
