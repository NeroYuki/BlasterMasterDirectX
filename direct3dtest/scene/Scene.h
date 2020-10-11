#pragma once
#include <vector>
#include "../gameObject/AllObject.h"


class Scene {
private:
	std::vector<GameObject*> objectPool;

public:
	Scene();
	void addObject(GameObject* obj);
	virtual void initScene() = 0;
	virtual void handlingInput() = 0;
	virtual void update(DWORD dt);
	void render();

	virtual void onCreate() {}
	virtual void onDestroy() {}
	virtual void onActivate() {}
	virtual void onDeactivated() {}
};