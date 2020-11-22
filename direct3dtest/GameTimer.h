#pragma once

#define TIMER_INACTIVE 0
#define TIMER_STARTED 1
#define TIMER_ACTIVE 2
#define TIMER_ENDED 3

class GameTimer {
private:
	bool isStart = false;
	long current = 0;
	long interval = 0;
public:
	GameTimer(long interval);
	void start();
	void restart();
	void stop();
	void pause();
	short update(long dt);
	short peekState();
	bool isStarted() { return isStart; }
	long getInterval() { return this->interval; }
	void setInterval(long interval) { this->interval = interval; }
};