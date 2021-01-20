#include "DebugScene.h"

DebugScene::DebugScene(SceneStateMachine* sceneState) : Scene(sceneState)
{
	initScene();
	bgTexture_id = 6;
	fgTexture_id = 8;
	activeSection = 0;
	sectionSwitchTimer = new GameTimer(3000);
	switchSceneTimer = new GameTimer(500);
}

void DebugScene::initScene()
{
	p_stack = new std::stack<Player*>();
	JasonTop* s = new JasonTop(90, 1420, 1);
	p_stack->push(s);
	//initially put every object into its respective grid
	//this->addObject(sophia);
	this->addObject(s);
	cam->setFollow(p_stack->top());

}

void DebugScene::handlingInput()
{
	int control_state = 0;
	if (p_stack->top()->getInvincible() != 1) {

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

void DebugScene::update(DWORD dt) {
	Scene::update(dt);
	heatlhbar->update(cam);
	gunBar->update(cam);
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
	if (p_stack->top()->getIsChangeScene() == 1) {
		if (!switchSceneTimer->isStarted())
			switchSceneTimer->start();
		p_stack->top()->setIsChangeScence(0);
	}

	short timerState = sectionSwitchTimer->update(dt);
	short timerState2 = switchSceneTimer->update(dt);
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
		p_stack->top()->getPos(spawnerX, spawnerY);
	}
	if (timerState2 == TIMER_STARTED) {
		ScenePortal* portal = p_stack->top()->getScenePortal();
		if (portal != NULL) {
			int sceneid = sceneState->getSceneByLabel("Overworld");

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

void DebugScene::onActivate() {

	if (PreScenePortal != NULL) {
		p_stack->top()->setForceControlState(IDLE);
		p_stack->top()->setIgnoreCollision(false);
		int section = PreScenePortal->getSectionEnd();
		this->spawnerX= PreScenePortal->getLx();
		this->spawnerY= PreScenePortal->getLy();
		p_stack->top()->resetPlayer(spawnerX, spawnerY);
		p_stack->top()->setActiveSection(section);
		activeSection = p_stack->top()->getActiveSection();
		cam->update(this->sectionGraph.getSection(section));
		cam->setForceVeloc(0, 0);
		for (std::vector<ObjectGrid*>::iterator it = objectGridMap.begin(); it != objectGridMap.end(); ++it)
		{
			(*it)->updateGridPos();
		}
		this->PreScenePortal = NULL;
		heatlhbar->setFollow(p_stack->top());
		gunBar->setFollow(p_stack->top());
	}

}
void DebugScene::onDeAtivate() {
	if (isresetenemy == 1)
		this->resetSceneEnemy();
	isresetenemy = -1;
}
void DebugScene::renderHUD()
{
	heatlhbar->render();
	gunBar->render();
}


DebugScene::~DebugScene() {
	//deallocate player control stack and object pool
}


void abandoned() {
	//int res_jsTop = 0;
	//int res_js = 0;
	//int res_sophia = 0;
	//if (InputHandler::getInstance()->isKeyDown(DIK_W)) {
	//	jsTop->changeState(TOP_JASON_WALK_UP);
	//	res_jsTop += UP;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_A)) {
	//	jsTop->changeState(TOP_JASON_WALK_LEFT);
	//	res_jsTop += LEFT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_S)) {
	//	jsTop->changeState(TOP_JASON_WALK_DOWN);
	//	res_jsTop += DOWN;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_D)) {
	//	jsTop->changeState(TOP_JASON_WALK_RIGHT);
	//	res_jsTop += RIGHT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT)) {
	//	if (js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_CRAW_RIGHT);
	//	}
	//	else //if (js->getState() == JASON_IDLE_LEFT || js->getState() == JASON_WALK_LEFT || js->getState() == JASON_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_WALK_RIGHT);
	//	}
	//	if (sophia->getState() == SOPHIA_IDLE_LEFT || sophia->getState() == SOPHIA_MOVE_LEFT)
	//	{
	//		sophia->changeState(SOPHIA_TURN_RIGHT);
	//		res_sophia -= RIGHT;
	//	}
	//	else
	//	{
	//		sophia->changeState(SOPHIA_MOVE_RIGHT);
	//	}
	//	res_js += RIGHT;
	//	res_sophia += RIGHT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)) {
	//	if (js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_CRAW_LEFT);
	//	}
	//	else //if (js->getState() == JASON_IDLE_LEFT || js->getState() == JASON_WALK_LEFT || js->getState() == JASON_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_WALK_LEFT);
	//	}
	//	if (sophia->getState() == SOPHIA_IDLE_RIGHT || sophia->getState() == SOPHIA_MOVE_RIGHT)
	//	{
	//		sophia->changeState(SOPHIA_TURN_LEFT);
	//		res_sophia -= LEFT;
	//	}
	//	else
	//	{
	//		sophia->changeState(SOPHIA_MOVE_LEFT);
	//	}
	//	res_sophia += LEFT;
	//	res_js += LEFT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_DOWN)) {
	//	js->changeState(COMMON_JASON_CRAW_IDLE);
	//	js->setCrawState(true);
	//}

	//if (InputHandler::getInstance()->isKeyDown(DIK_UP)) {
	//	if (js->getState() == js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//		js->changeState(COMMON_JASON_IDLE);
	//	js->setCrawState(false);
	//}

	//if (InputHandler::getInstance()->isKeyDown(DIK_X)) {
	//	if (!js->getCrawState())
	//	{
	//		if (js->getState() == JASON_IDLE_LEFT || js->getState() == JASON_WALK_LEFT)
	//		{
	//			js->changeState(JASON_JUMP_LEFT);
	//		}
	//		else if (js->getState() == JASON_IDLE_RIGHT || js->getState() == JASON_WALK_RIGHT)
	//		{
	//			js->changeState(JASON_JUMP_RIGHT);
	//		}
	//		res_js += JUMP;
	//	}
	//	if (sophia->getState() == SOPHIA_MOVE_RIGHT || sophia->getState() == SOPHIA_IDLE_RIGHT) {
	//		sophia->changeState(SOPHIA_JUMP_RIGHT);
	//	}
	//	else if (sophia->getState() == SOPHIA_MOVE_LEFT || sophia->getState() == SOPHIA_MOVE_LEFT) {
	//		sophia->changeState(SOPHIA_JUMP_LEFT);
	//	}
	//	res_sophia += JUMP;
	//}
	//jsTop->setControlState(res_jsTop);
	//js->setControlState(res_js);
	//sophia->setControlState(res_sophia);
	//if (res_js == 0) {
	//	if (js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//		js->changeState(COMMON_JASON_CRAW_IDLE);
	//	else
	//		js->changeState(COMMON_JASON_IDLE);
	//}
	//if (res_jsTop == 0) {
	//	jsTop->changeState(COMMON_PLAYER_IDLE);
	//}
	//if (res_sophia == 0) {
	//	sophia->changeState(COMMON_SOPHIA_IDLE);
	//}
}