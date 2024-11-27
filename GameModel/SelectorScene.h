#pragma once
#include "Scene.h"
#include<iostream>

class SelectorScene :public Scene {
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void onEnter() override {
		std::cout << "进入角色选择场景" << std::endl;
	};
	void onUpdate(const int deltaTime) override {
		std::cout << "更新角色选择场景" << std::endl;
	};
	void onDraw(const Camera& camera) override {
		outtextxy(100, 100, _T("角色选择场景"));
	};
	void onEvent(const ExMessage& msg) override {
		std::cout << "处理角色选择场景事件" << std::endl;
	};
	void onExit() override {
		std::cout << "退出角色选择场景" << std::endl;
	};
};