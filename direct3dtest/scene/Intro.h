#pragma once
#include "Scene.h"
#include "../InputHandler.h"

class Intro : public Scene
{
private:
	int introID;
	GameTimer* timerunFirstIntro;
	GameTimer* timerunReady;
public:
	Intro(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void render();
	void changeIntroID(int newID);
	void onActivate();
	void onDeactivated();
};


