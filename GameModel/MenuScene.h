#pragma once
#include "Scene.h"
#include<iostream>
#include"SceneManager.h"

extern SceneManager sceneManager;

class MenuScene :public Scene {
public:
	MenuScene() = default;
	~MenuScene() = default;

	void onEnter() override {
		std::cout << "进入菜单场景" << std::endl;
	};
	void onUpdate(const int deltaTime) override {
		std::cout << "更新菜单场景" << std::endl;
	};
	void onDraw() override {
		outtextxy(100, 100, _T("当前为菜单场景，按任意键切换到游戏场景"));
	};
	void onEvent(const ExMessage& msg) override {
		if (msg.message == WM_KEYDOWN) {
			sceneManager.changeScene(SceneEnums::GAME);
		}
	};
	void onExit() override {
		std::cout << "退出菜单场景" << std::endl;
	};
};