#pragma once
#include "Scene.h"
#include<iostream>
#include"Atlas.h"
#include"Animation.h"
#include"Camera.h"
#include"Vector2d.h"

extern Atlas atlasPlayerRight;

class GameScene :public Scene {
public:
	GameScene() = default;
	~GameScene() = default;

	void onEnter() override {
		this->animationPlayerRight.setAtlas(&atlasPlayerRight);
		this->animationPlayerRight.setInterval(75);
		this->animationPlayerRight.setLoop(true);
	};
	void onUpdate(const int deltaTime) override {
		this->camera.onUpdate(deltaTime);
		this->animationPlayerRight.onUpdate(deltaTime);
	};
	void onDraw() override {
		const Vector2D& position = this->camera.getPosition();
		this->animationPlayerRight.onDraw(500 - position.x, 500 - position.y);
	};
	void onEvent(const ExMessage& msg) override {

		if (msg.message == WM_KEYDOWN) {
			camera.shake(10, 350);
		}
	};
	void onExit() override {
		std::cout << "退出游戏场景" << std::endl;
	};
private:
	Animation animationPlayerRight;
	Camera camera;
};