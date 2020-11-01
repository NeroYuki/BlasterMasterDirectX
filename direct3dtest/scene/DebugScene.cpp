#include "DebugScene.h"

DebugScene::DebugScene(SceneStateMachine* sceneState) : Scene(), sceneState(sceneState)
{
	initScene();
	bgTexture_id = 6;
}

void DebugScene::initScene()
{
	this->addObject(new Worm(30, 30, 1));
	this->addObject(new Floater(200, 30, 1));
	p = new Player(30, 180, 1);
	this->addObject(p);
	cam->setFollow(p);
}

void DebugScene::handlingInput()
{
	int res = 0;
	if (InputHandler::getInstance()->isKeyDown(DIK_W)) {
		p->changeState(TOP_JASON_WALK_UP);
		res += JASON_UP;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_A)) {
		p->changeState(TOP_JASON_WALK_LEFT);
		res += JASON_LEFT;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_S)) {
		p->changeState(TOP_JASON_WALK_DOWN);
		res += JASON_DOWN;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_D)) {
		p->changeState(TOP_JASON_WALK_RIGHT);
		res += JASON_RIGHT;
	}
	p->setControlState(res);
	if (res == 0) {
		p->changeState(COMMON_PLAYER_IDLE);
	}
}

void DebugScene::update() {

}
