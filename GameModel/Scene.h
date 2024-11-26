#pragma once
#include<graphics.h>

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	virtual void onEnter() {};
	virtual void onUpdate(int deltaTime) {};
	virtual void onDraw() {};
	virtual void onEvent(const ExMessage& msg) {};
	virtual void onExit() {};
};
