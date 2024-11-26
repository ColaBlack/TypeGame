#pragma once
#include "Scene.h"
#include<iostream>

class GameScene :public Scene {
public:
	GameScene() = default;
	~GameScene() = default;

	void onEnter() override {
		std::cout << "进入游戏场景" << std::endl;
	};
	void onUpdate(int deltaTime) override {
		std::cout << "更新游戏场景" << std::endl;
	};
	void onDraw() override {
		outtextxy(100, 100, _T("游戏场景"));
	};
	void onEvent(const ExMessage& msg) override {
		std::cout << "处理游戏场景事件" << std::endl;
	};
	void onExit() override {
		std::cout << "退出游戏场景" << std::endl;
	};
};