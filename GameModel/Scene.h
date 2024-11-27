#pragma once
#include<graphics.h>
#include"Camera.h"

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	virtual void onEnter() {};
	virtual void onUpdate(const int deltaTime) {};
	virtual void onDraw(const Camera& camera) {};
	virtual void onEvent(const ExMessage& msg) {};
	virtual void onExit() {};
};
