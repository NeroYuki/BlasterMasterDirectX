#include "DebugScene.h"

DebugScene::DebugScene(SceneStateMachine* sceneState) : Scene(), sceneState(sceneState)
{
	initScene();
}

void DebugScene::initScene()
{
	this->addObject(new Worm(30, 30, 1));
	this->addObject(new Floater(200, 30, 1));
	p = new Player(30, 180, 1);
	this->addObject(p);
	
}

void DebugScene::handlingInput()
{
	if (InputHandler::getInstance()->isKeyDown(DIK_W)) {
		p->changeState(TOP_JASON_WALK_UP);
	}
	else if (InputHandler::getInstance()->isKeyDown(DIK_A)) {
		p->changeState(TOP_JASON_WALK_LEFT);
	}
	else if (InputHandler::getInstance()->isKeyDown(DIK_S)) {
		p->changeState(TOP_JASON_WALK_DOWN);
	}
	else if (InputHandler::getInstance()->isKeyDown(DIK_D)) {
		p->changeState(TOP_JASON_WALK_RIGHT);
	}
	else {
		p->changeState(COMMON_PLAYER_IDLE);
	}
}

void DebugScene::update() {

}
