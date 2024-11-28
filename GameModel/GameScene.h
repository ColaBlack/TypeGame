#pragma once
#include "Scene.h"
#include<iostream>
#include"Atlas.h"
#include"Animation.h"
#include"Camera.h"
#include"Vector2d.h"
#include"Stage.h"
#include"Path.h"

int countDown = 4;

Stage stage = Stage::Waiting;

int playerId = 0;
std::atomic<int> progress1 = -1;
std::atomic<int> progress2 = -1;

//要打的字数
int totalChar = 0;
//要打的全部文本
std::string text;
//每行的文本
std::vector<std::string> lineList;

//玩家1资源
Atlas atlas1PIdleUp;
Atlas atlas1PIdleDown;
Atlas atlas1PIdleLeft;
Atlas atlas1PIdleRight;
Atlas atlas1PRunUp;
Atlas atlas1PRunDown;
Atlas atlas1PRunLeft;
Atlas atlas1PRunRight;

//玩家2资源
Atlas atlas2PIdleUp;
Atlas atlas2PIdleDown;
Atlas atlas2PIdleLeft;
Atlas atlas2PIdleRight;
Atlas atlas2PRunUp;
Atlas atlas2PRunDown;
Atlas atlas2PRunLeft;
Atlas atlas2PRunRight;

//UI资源
IMAGE imageUI1;
IMAGE imageUI2;
IMAGE imageUI3;
IMAGE imageUIFight;
IMAGE imageUITextbox;
IMAGE imageBackground;

//服务器地址
std::string address;
//http客户端
httplib::Client* client=nullptr;

//玩家移动路径
Path path = Path({ {842,842},{1322,842},{1322,442 },{2762,442},{2762,842},{3162,842},{3162,1722},{2122,1722},{2122,1562},{842,1562},{842,842} });

class GameScene :public Scene {
public:
	GameScene() = default;
	~GameScene() = default;

	void onEnter() override {

	};
	void onUpdate(const int deltaTime) override {
		this->camera.onUpdate(deltaTime);
	};
	void onDraw(const Camera& camera) override {
		const Vector2D& position = this->camera.getPosition();
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
	Camera camera;
};