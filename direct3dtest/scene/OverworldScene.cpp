#include "OverworldScene.h"

OverworldScene::OverworldScene(SceneStateMachine* sceneState) : Scene(), sceneState(sceneState)
{
	initScene();
	bgTexture_id = 5;
	fgTexture_id = 9;
	activeSection = -1;
}

void OverworldScene::initScene()
{
	p_stack = new std::stack<Player*>();
	Sophia* s = new Sophia(88, 3079, 1);
	//JasonTop* s = new JasonTop(90, 1420, 1);
	p_stack->push(s);
	//initially put every object into its respective grid
	//this->addObject(sophia);
	this->addObject(s);
	cam->setFollow(p_stack->top());
}

void OverworldScene::handlingInput()
{
	int control_state = 0;
	if (InputHandler::getInstance()->isKeyDown(DIK_DOWN)) {
		control_state += DOWN;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_UP)) {
		control_state += UP;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)) {
		control_state += LEFT;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT)) {
		control_state += RIGHT;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_Z)) {
		control_state += PRIMARY;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_X)) {
		control_state += SECONDARY;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_LSHIFT)) {
		//spawn a small jason and switch 
	}
	p_stack->top()->setControlState(control_state);
}

void OverworldScene::update()
{
}
