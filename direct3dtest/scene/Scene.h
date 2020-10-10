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
	void render();
};