#pragma once

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
	bool update(long dt);
	long getInterval() { return this->interval; }
	void setInterval(long interval) { this->interval = interval; }
};