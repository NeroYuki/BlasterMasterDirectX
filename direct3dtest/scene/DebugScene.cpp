#include "DebugScene.h"

DebugScene::DebugScene(SceneStateMachine* sceneState) : Scene(), sceneState(sceneState)
{
	initScene();
}

void DebugScene::initScene()
{
	this->addObject(new Worm(30, 30, 1));
}

void DebugScene::handlingInput()
{
	if (InputHandler::getInstance()->isKeyDown(DIK_W)) {
		// Handling key input here
		//DebugOut("W");
	}
}

void DebugScene::update() {

}
