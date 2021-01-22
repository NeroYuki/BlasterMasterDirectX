#include "SharedData.h"

SharedData::SharedData() {
	homingMissle = 15;
	x3Missle = 15;
	lightning = 15;
	weapon = 1;
	remaininglive = 1;
	upgrade =0;
	color = 255;
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

int SharedData::getColor()
{	
	color = color - 15;
	if (color < 100) color = 255;
	return color;
}
