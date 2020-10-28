#pragma once
#include "Scene.h"

class GameScene : public Scene {
private:
	virtual void loadMapdata();
public:
	GameScene();
	virtual void initScene() = 0;
	virtual void handlingInput() = 0;
};