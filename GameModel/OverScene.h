#pragma once
#include "Scene.h"
#include<iostream>

class OverScene :public Scene {
public:
	OverScene() = default;
	~OverScene() = default;

	void onEnter() override {
		std::cout << "进入结算场景" << std::endl;
	};
	void onUpdate(const int deltaTime) override {
		std::cout << "更新结算场景" << std::endl;
	};
	void onDraw() override {
		outtextxy(100, 100, _T("结算场景"));
	};
	void onEvent(const ExMessage& msg) override {
		std::cout << "处理结算场景事件" << std::endl;
	};
	void onExit() override {
		std::cout << "退出结算场景" << std::endl;
	};
};