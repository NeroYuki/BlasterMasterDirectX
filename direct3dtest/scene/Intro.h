#pragma once
#include "Scene.h"
#include "../SceneStateMachine.h"
#include "../InputHandler.h"

class Intro : public Scene
{
private:
	SceneStateMachine* sceneState;
	int introID;
	GameTimer* timerunFirstIntro;
public:
	Intro(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void render();
	void changeIntroID(int newID);
};


