#include "SharedData.h"

SharedData::SharedData() {
	homingMissle = 15;
	x3Missle = 15;
	lightning = 15;
	weapon = 1;
	remaininglive = 1;
	upgrade = 5;
}
SharedData* SharedData::instance = nullptr;
SharedData* SharedData::getInstance()
{
	if (!instance)
	{
		instance = new SharedData;
	}
	return instance;
}
