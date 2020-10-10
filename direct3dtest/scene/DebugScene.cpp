#include "DebugScene.h"

DebugScene::DebugScene() : Scene()
{
	initScene();
}

void DebugScene::initScene()
{
	this->addObject(new Worm(30, 30, 1));
}
