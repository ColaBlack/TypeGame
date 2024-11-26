#pragma once
#include "Scene.h"
#include<iostream>

class MenuScene :public Scene {
public:
	MenuScene() = default;
	~MenuScene() = default;

	void onEnter() override {
	std::cout << "进入菜单场景" << std::endl;
	};
	void onUpdate(int deltaTime) override {
	std::cout << "更新菜单场景" << std::endl;
	};
	void onDraw() override {
	outtextxy(100, 100, _T("菜单场景"));
	};
	void onEvent(const ExMessage& msg) override {
	std::cout << "处理菜单场景事件" << std::endl;
	};
	void onExit() override{
	std::cout << "退出菜单场景" << std::endl;
	};
};