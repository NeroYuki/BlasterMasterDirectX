#include "DugeonScene.h"

DungeonScene::DungeonScene(SceneStateMachine* sceneState) : Scene(sceneState)
{
	initScene();
	bgTexture_id = 6;
	fgTexture_id = 8;
	activeSection = 0;
	sectionSwitchTimer = new GameTimer(3000);
}

void DungeonScene::initScene()
{
	p_stack = new std::stack<Player*>();
	this->addObject(new Worm(30, 30, 1));
	this->addObject(new Floater(200, 30, 1));
	JasonTop* s = new JasonTop(90, 1420, 1);
	p_stack->push(s);
	//initially put every object into its respective grid
	//this->addObject(sophia);
	this->addObject(s);
	cam->setFollow(p_stack->top());
}

void DungeonScene::handlingInput()
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

void DungeonScene::update(DWORD dt) {
	Scene::update(dt);

	//attempt section switching logic
	if (p_stack->top()->getActiveSection() != activeSection) {
		if (!sectionSwitchTimer->isStarted())
			sectionSwitchTimer->start();
	}

	short timerState = sectionSwitchTimer->update(dt);
	if (timerState == TIMER_STARTED) {
		p_stack->top()->setIgnoreCollision(true);
		//find the corresponded portal
		std::vector<SectionGraphEdge>* portalList = sectionGraph.getLinkedPortalList(activeSection);
		for (int i = 0; i < portalList->size(); i++) {
			if (portalList->at(i).dst == p_stack->top()->getActiveSection()) {
				Portal* checking_portal = portalList->at(i).p;

				float lx = checking_portal->getLx();
				float ly = checking_portal->getLy();
				int forceControlState = 0;

				if (lx > 0) forceControlState += RIGHT;
				if (lx < 0) forceControlState += LEFT;
				if (ly > 0) forceControlState += DOWN;
				if (ly < 0) forceControlState += UP;
				p_stack->top()->setForceControlState(forceControlState);

				long interval = max(abs(lx) / PLAYER_WALKING_SPEED, abs(ly) / PLAYER_WALKING_SPEED) + 500;
				sectionSwitchTimer->setInterval(interval);

				float lcx = 0, lcy = 0;
				if (lx > 0) { lcx = cam->getW(); }
				if (lx < 0) { lcx = -cam->getW(); }
				if (ly > 0) { lcy = cam->getH() + 32; }
				if (ly < 0) { lcy = -(cam->getH() + 32); }

				cam->setForceVeloc(lcx / interval, lcy / interval);
				cam->updateWithForceVeloc(dt);
			}
		}
	}
	else if (timerState == TIMER_ACTIVE) {
		cam->updateWithForceVeloc(dt);
	}
	else if (timerState == TIMER_ENDED) {
		p_stack->top()->setForceControlState(IDLE);
		p_stack->top()->setIgnoreCollision(false);
		activeSection = p_stack->top()->getActiveSection();
		cam->setForceVeloc(0, 0);
	}
}

DungeonScene::~DungeonScene() {
	//deallocate player control stack and object pool
}
