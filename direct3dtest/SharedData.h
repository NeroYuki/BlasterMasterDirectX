#pragma once
#include <stdlib.h>

class SharedData {
private:
	static SharedData* instance;
	SharedData();
public:
	int homingMissle;
	int x3Missle;
	int lightning;
	int weapon;
	int remaininglive;
	int upgrade;
	static SharedData* getInstance();
	float getRandomNumber() { return rand();}
};