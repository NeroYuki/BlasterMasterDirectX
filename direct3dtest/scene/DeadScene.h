#pragma once
#include "Scene.h"
#include "../InputHandler.h"
#include "CharsetShow.h"

class DeadScene : public Scene {
private:
	int choice = 1;
	int live;
	CharsetShow* charsets[4];
	int isupkeydown = 0, isdownkeydown = 0;
public:
	DeadScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void onActivate();
	void onDeactivated();
	void render();
	int getCurrentSceneNumber() { return 2; }
};
