#include "OverworldScene.h"

OverworldScene::OverworldScene(SceneStateMachine* sceneState) : Scene(sceneState)
{
	initScene();
	bgTexture_id = 5;
	fgTexture_id = 9;
	activeSection = 0;
	sectionSwitchTimer = new GameTimer(3000);
	blockShiftTimer = new GameTimer(1000);
	switchSceneTimer = new GameTimer(500);
}

void OverworldScene::initScene()
{
	p_stack = new std::stack<Player*>();
	spawnerX = 100;
	spawnerY = 3000;
	Sophia* s = new Sophia(spawnerX, spawnerY, 1);
	p_stack->push(s);
	this->addObject(s);
	p_stack->top()->setActiveSection(0);
	cam->setFollow(p_stack->top());
	heatlhbar->setFollow(p_stack->top());
}

void OverworldScene::handlingInput()
{
	int control_state = 0;
	if (p_stack->top()->getInvincible() != 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_H)) {
			p_stack->top()->PlayerHeal(16);
		}
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
					p_stack->top()->setInvincible(2);
					p_stack->top()->getPos(x, y);
					Jason* new_jason = new Jason(x, y - 4, 1, p_stack->top()->getActiveSection());
					new_jason->setFollow(p_stack->top());
					p_stack->push(new_jason);
					this->addObject(new_jason);
					cam->setFollow(p_stack->top());
					heatlhbar->setFollow(p_stack->top());
					blockShiftTimer->restart();
				}
				else if (dynamic_cast<Jason*>(p_stack->top())) {
					Jason* jason_p = dynamic_cast<Jason*>(p_stack->top());
					if (jason_p->getIsCloseToSophia()) {
						jason_p->unfollow();
						p_stack->pop();
						this->removeObject(jason_p);
						cam->setFollow(p_stack->top());
						p_stack->top()->setInvincible(0);
						heatlhbar->setFollow(p_stack->top());
					}
					blockShiftTimer->restart();
				}
			}

		}
		p_stack->top()->setControlState(control_state);
		if (InputHandler::getInstance()->isKeyDown(DIK_RETURN)) {
			isEnterKeyDown = 1;
		}
		if (isEnterKeyDown == 1) {
			if (InputHandler::getInstance()->isKeyDown(DIK_RETURN) == 0) {
				isEnterKeyDown = 0;
				int sceneid = sceneState->getSceneByLabel("Menu");
				sceneState->switchToScene(sceneid);
			}
		}
	}
	
}

void OverworldScene::update(DWORD dt)
{
	Scene::update(dt);
	heatlhbar->update(cam);
	BulletManager* r = BulletManager::getinstance();
	if (r->getBullet()->size() != 0) {
		for (int i = 0; i < r->getBullet()->size(); i++)
		{
			this->addObject(r->getBullet()->at(i));
		}
		r->getBullet()->clear();
	}
	if (r->getDeleteBullet()->size() != 0) {
		for (int i = 0; i < r->getDeleteBullet()->size(); i++) 
		{
			this->removeObject(r->getDeleteBullet()->at(i));
		}
		r->getDeleteBullet()->clear();
	}
	CollectableManager* c = CollectableManager::getinstance();
	if (c->getCollectable()->size() != 0) {
		for (int i = 0; i < c->getCollectable()->size(); i++)
		{
			this->addObject(c->getCollectable()->at(i));
		}
		c->getCollectable()->clear();
	}
	//attempt section switching logic
	if (p_stack->top()->getActiveSection() != activeSection) {
		if (!sectionSwitchTimer->isStarted())
			sectionSwitchTimer->start();
	}
	if (p_stack->top()->getIsChangeScene() == 1 ) {
		if (!switchSceneTimer->isStarted())
			switchSceneTimer->start();
		p_stack->top()->setIsChangeScence(0);
	}
	short timerState = sectionSwitchTimer->update(dt);
	short timerState2 = switchSceneTimer->update(dt);
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
		p_stack->top()->getPos(spawnerX, spawnerY);
	}
	if (timerState2 == TIMER_STARTED) {
		ScenePortal* portal = p_stack->top()->getScenePortal();
		if (portal != NULL) {
			int sceneid =sceneState->getSceneByLabel("Debug");

			Scene* returnScene = sceneState->getSceneById(sceneid);
			returnScene->PreScenePortal = portal;

			sceneState->switchToScene(sceneid);
		}
	}
	if (p_stack->top()->getisDie() == 2) {
		if (dynamic_cast<Jason*>(p_stack->top())) {
			Jason* jason_p = dynamic_cast<Jason*>(p_stack->top());
			jason_p->unfollow();
			p_stack->pop();
			this->removeObject(jason_p);
			p_stack->top()->resetPlayer(spawnerX, spawnerY);
			cam->setFollow(p_stack->top());
			heatlhbar->setFollow(p_stack->top());
		}
		else {
			p_stack->top()->resetPlayer(spawnerX, spawnerY);
			cam->setFollow(p_stack->top());
			heatlhbar->setFollow(p_stack->top());
		}
		int sceneid = sceneState->getSceneByLabel("DeadScene");
		isresetenemy = 1;
		sceneState->switchToScene(sceneid);
	}
}

void OverworldScene::onActivate()
{
	//if (PreScenePortal != NULL) {
	//	//p_stack->top()->setForceControlState(IDLE);
	//	//p_stack->top()->setIgnoreCollision(false);
	//	int section = PreScenePortal->getSectionEnd();
	//	//p_stack->top()->setPos(PreScenePortal->getLx(), PreScenePortal->getLy());
	//	p_stack->top()->setActiveSection(section);
	//	activeSection = p_stack->top()->getActiveSection();
	//	cam->update(this->sectionGraph.getSection(section));
	//	//cam->setForceVeloc(0, 0);
	for (std::vector<ObjectGrid*>::iterator it = objectGridMap.begin(); it != objectGridMap.end(); ++it)
	{
		(*it)->updateGridPos();
	}
	//	this->PreScenePortal = NULL;
	//}
	if (!SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_BG_AREA2))
	SoundManager::getInstance()->PlayLoop(eSoundId::SOUND_BG_AREA2);
}

void OverworldScene::renderHUD() {
	heatlhbar->render();
}

void OverworldScene::onDeactivated()
{
	//if(SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_BG_AREA2))
	//SoundManager::getInstance()->Stop(eSoundId::SOUND_BG_AREA2);
	if(isresetenemy==1)
	this->resetSceneEnemy();
	isresetenemy = -1;
}
