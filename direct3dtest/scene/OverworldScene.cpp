#include "OverworldScene.h"

OverworldScene::OverworldScene(SceneStateMachine* sceneState) : Scene(), sceneState(sceneState)
{
	initScene();
	bgTexture_id = 5;
	fgTexture_id = 9;
	activeSection = 0;
	sectionSwitchTimer = new GameTimer(3000);
	blockShiftTimer = new GameTimer(1000);
}

void OverworldScene::initScene()
{
	p_stack = new std::stack<Player*>();
	Sophia* s = new Sophia(88, 3000, 1);
	p_stack->push(s);
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
		if (blockShiftTimer->peekState() != TIMER_ACTIVE) {
			if (dynamic_cast<Sophia*>(p_stack->top())) {
				float x, y;
				p_stack->top()->getPos(x, y);
				Jason* new_jason = new Jason(x, y - 4, 1, p_stack->top()->getActiveSection());
				p_stack->push(new_jason);
				this->addObject(new_jason);
				cam->setFollow(p_stack->top());
				blockShiftTimer->restart();
			}
			else if (dynamic_cast<Jason*>(p_stack->top())) {
				Jason* jason_p = dynamic_cast<Jason*>(p_stack->top());
				if (jason_p->getIsCloseToSophia()) {
					p_stack->pop();
					this->removeObject(jason_p);
					cam->setFollow(p_stack->top());
				}
				blockShiftTimer->restart();
			}
		}
	}
	p_stack->top()->setControlState(control_state);
}

void OverworldScene::update(DWORD dt)
{
	Scene::update(dt);

	//attempt section switching logic
	if (p_stack->top()->getActiveSection() != activeSection) {
		if (!sectionSwitchTimer->isStarted())
			sectionSwitchTimer->start();
	}

	short timerState = sectionSwitchTimer->update(dt);
	blockShiftTimer->update(dt);

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

				long interval = max(abs(lx) / SOPHIA_MOVE_SPEED_CAP, abs(ly) / SOPHIA_MOVE_SPEED_CAP) + 300;
				//change scrolling interval if jason is going throught the portal
				if (dynamic_cast<Jason*>(p_stack->top())) {
					interval = max(abs(lx) / JASON_MOVE_SPEED_CAP, abs(ly) / JASON_MOVE_SPEED_CAP) + 300;
				}
				sectionSwitchTimer->setInterval(interval);

				float lcx = 0, lcy = 0;
				if (lx > 0) { lcx = (cam->getW()); }
				if (lx < 0) { lcx = -cam->getW(); }
				if (ly > 0) { lcy = cam->getH(); }
				if (ly < 0) { lcy = -cam->getH(); }

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
