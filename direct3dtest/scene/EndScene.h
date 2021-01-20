#pragma once
#include "Scene.h"
#include "../SceneStateMachine.h"
#include "../InputHandler.h"
class EndScene :
	public Scene
{
private:
	SceneStateMachine* sceneState;
	GameTimer* timerunEndingAni;
	GameTimer* timerunTreeAni;
	bool startTrans;
	bool stopTrans;
	int countTreeAni;
public:
	EndScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void render();

};