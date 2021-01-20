#pragma once
#include "Scene.h"
#include "../InputHandler.h"
#include "CharsetShow.h"
//class CharsetShow {
//public:
//	int x, y;
//	int state;
//	CharsetShow(int x, int y, int state) { this->x = x; this->y = y, this->state = state; };
//};
class MenuScene : public Scene {
private:
	GameTimer* switchSceneTimer;
	int choice = 1;
	CharsetShow* charsets[9];
	int isleftkeydown = 0, isrightkeydown = 0;
public:
	MenuScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void onActivate();
	void onDeactivated();
	void render();
};
