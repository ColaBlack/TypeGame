#pragma once
#include "Scene.h"
#include<iostream>
#include"Atlas.h"
#include"Camera.h"
#include"Vector2d.h"
#include"Stage.h"
#include"Path.h"
#include"AudioUtils.h"
#include"Player.h"
#include"stringUtils.h"

// 玩家1资源
extern Atlas atlas1PIdleUp;
extern Atlas atlas1PIdleDown;
extern Atlas atlas1PIdleLeft;
extern Atlas atlas1PIdleRight;
extern Atlas atlas1PRunUp;
extern Atlas atlas1PRunDown;
extern Atlas atlas1PRunLeft;
extern Atlas atlas1PRunRight;

// 玩家2资源
extern Atlas atlas2PIdleUp;
extern Atlas atlas2PIdleDown;
extern Atlas atlas2PIdleLeft;
extern Atlas atlas2PIdleRight;
extern Atlas atlas2PRunUp;
extern Atlas atlas2PRunDown;
extern Atlas atlas2PRunLeft;
extern Atlas atlas2PRunRight;

//UI资源
extern IMAGE imageUI1;
extern IMAGE imageUI2;
extern IMAGE imageUI3;
extern IMAGE imageUIFight;
extern IMAGE imageUITextbox;
extern IMAGE imageBackground;

int countDown = 4;

Stage stage = Stage::Waiting;

//http客户端
httplib::Client* client = nullptr;
extern std::string address;
int playerId = 0;
std::atomic<int> progress1 = -1;
std::atomic<int> progress2 = -1;

//要打的字数
int totalChar = 0;
//要打的全部文本
std::string text="no text";
//每行的文本
std::vector<std::string> lineList;
int lineIndex = 0;
int charIndex = 0;

//玩家移动路径
Path path = Path({ {842,842},{1322,842},{1322,442 },{2762,442},{2762,842},{3162,842},{3162,1722},{2122,1722},{2122,1562},{842,1562},{842,842} });

class GameScene :public Scene {
public:
	GameScene() = default;
	~GameScene() = default;

	void onEnter() override {
		client = new httplib::Client(address);
		client->set_keep_alive(true);

		httplib::Result res = client->Post("/user/login");

		if (!res || res->status != 200) {
			MessageBox(NULL, _T("登录失败，请检查网络连接"), _T("错误"), MB_OK);
			exit(-1);
		}
		playerId = std::stoi(res->body);

		if (playerId <= 0) {
			MessageBox(NULL, _T("游戏已经开始啦，请等待下一局"), _T("错误"), MB_OK);
			exit(-1);
		}
		if (playerId == 1) {
			progress1 = 0;
		}
		else {
			progress2 = 0;
		}

		text = client->Post("/data/get")->body;
		std::stringstream strStream(text);
		std::string line;
		while (std::getline(strStream, line)) {
			lineList.push_back(line);
			totalChar += line.length();
		}

		// 新开线程更新游戏进度
		std::thread([&]() {
			while (true) {
				using namespace std::chrono;

				std::string route = (playerId == 1) ? "/progress/exchange1" : "/progress/exchange2";
				std::string body = std::to_string(playerId == 1 ? progress1 : progress2);
				httplib::Result res = client->Post(route, body, "text/plain");
				if (!res || res->status != 200) {
					MessageBox(NULL, _T("网络错误，请检查网络连接"), _T("错误"), MB_OK);
					exit(-1);
				}
				int progress = std::stoi(res->body);
				if (playerId == 1) {
					progress2 = progress;
				}
				else {
					progress1 = progress;
				}

				std::this_thread::sleep_for(nanoseconds(1000000000 / 60));
			}
			}).detach();

		this->countDownTimer.setOneShot(false);
		this->countDownTimer.setWaitTime(1);
		this->countDownTimer.setOnFinishCallback([&]() {
			countDown--;
			switch (countDown) {
			case 3:
				playAudio(_T("ui_3"));
				break;
			case 2:
				playAudio(_T("ui_2"));
				break;
			case 1:
				playAudio(_T("ui_1"));
				break;
			case 0:
				playAudio(_T("ui_fight"));
				break;
			case -1:
				stage = Stage::Playing;
				playAudio(_T("bgm"), true);
				break;
			}
			});
		this->player1 = new Player(&atlas1PIdleUp, &atlas1PIdleDown, &atlas1PIdleLeft, &atlas1PIdleRight, &atlas1PRunUp, &atlas1PRunDown, &atlas1PRunLeft, &atlas1PRunRight);
		this->player2 = new  Player(&atlas2PIdleUp, &atlas2PIdleDown, &atlas2PIdleLeft, &atlas2PIdleRight, &atlas2PRunUp, &atlas2PRunDown, &atlas2PRunLeft, &atlas2PRunRight);
	};

	void onUpdate(const int deltaTime) override {
		if (stage == Stage::Waiting) {
			// 进入倒计时
			if (progress1 >= 0 && progress2 >= 0) {
				stage = Stage::Countdown;
			}
		}
		else if (stage == Stage::Countdown) {
			this->countDownTimer.onUpdate(deltaTime);
		}
		else if (stage == Stage::Playing) {
			// 有玩家获胜
			if ((progress1 >= totalChar) || (progress2 >= totalChar)) {
				stopAudio(_T("bgm"));
				playAudio(playerId == 1 ? _T("1p_win") : _T("2p_win"));
				MessageBox(NULL, progress1 >= totalChar ? _T("恭喜玩家1获胜！") : _T("恭喜玩家2获胜！"), _T("游戏结束"), MB_OK);
				exit(0);
			}

			this->player1->setPositionTarget(path.getPositionByProgress(progress1 / (double)totalChar));
			this->player2->setPositionTarget(path.getPositionByProgress(progress2 / (double)totalChar));

			this->player1->onUpdate(deltaTime);
			this->player2->onUpdate(deltaTime);

			// 摄像机跟随
			this->cameraPlayer.lookAt(playerId == 1 ? this->player1->getPosition() : this->player2->getPosition());
		}

	};
	void onDraw(const Camera& camera) override {
		if (stage == Stage::Waiting) {
			settextcolor(RGB(195, 195, 195));
			outtextxy(15, 675, _T("等待玩家加入..."));
		}
		else {
			//绘制背景图
			static const Rect bakcgroundRect = { 0,0,imageBackground.getwidth(),imageBackground.getheight() };
			putImageAlphaCam(this->cameraPlayer, &imageBackground, &bakcgroundRect);

			//绘制玩家
			if (player1->getPosition().y > player2->getPosition().y) {
				player2->onDraw(this->cameraPlayer);
				player1->onDraw(this->cameraPlayer);
			}
			else {
				player1->onDraw(this->cameraPlayer);
				player2->onDraw(this->cameraPlayer);
			}

			//绘制倒计时
			static const Rect ui3Rect = { 0,0,imageUI3.getwidth(),imageUI3.getheight() };
			static const Rect ui2Rect = { 0,0,imageUI2.getwidth(),imageUI2.getheight() };
			static const Rect ui1Rect = { 0,0,imageUI1.getwidth(),imageUI1.getheight() };
			static const Rect uiFightRect = { 0,0,imageUIFight.getwidth(),imageUIFight.getheight() };

			switch (countDown) {
			case 3:
				putImageAlphaCam(this->cameraUI, &imageUI3, &ui3Rect);
				break;
			case 2:
				putImageAlphaCam(this->cameraUI, &imageUI2, &ui2Rect);
				break;
			case 1:
				putImageAlphaCam(this->cameraUI, &imageUI1, &ui1Rect);
				break;
			case 0:
				putImageAlphaCam(this->cameraUI, &imageUIFight, &uiFightRect);
				break;
			}

			if (stage == Stage::Playing) {
				static const Rect textboxRect = { 0,720 - imageUITextbox.getheight(),imageUITextbox.getwidth(),imageUITextbox.getheight() };
				if (lineList.size() > 0) {
					//编码转换
					std::wstring wstrLine = string2wstring(lineList[lineIndex].c_str());
					std::wstring wstrCompleted = string2wstring(lineList[lineIndex].substr(0, charIndex).c_str());

					//绘制UI文本框
					putImageAlphaCam(this->cameraUI, &imageUITextbox, &textboxRect);
					settextcolor(RGB(125, 125, 125));
					outtextxy(187, textboxRect.y + 67, wstrLine.c_str());
					settextcolor(RGB(25, 25, 25));
					outtextxy(185, textboxRect.y + 65, wstrLine.c_str());
					settextcolor(RGB(0, 149, 217));
					outtextxy(185, textboxRect.y + 65, wstrCompleted.c_str());
				}
			}
		}
	};
	void onEvent(const ExMessage& msg) override {
		if (stage != Stage::Playing) {
			return;
		}

		if (msg.message == WM_CHAR && lineIndex < lineList.size()) {
			const std::string& line = lineList[lineIndex];
			if (line[charIndex] == msg.ch) {
				switch (rand() % 4) {
				case 0:
					playAudio(_T("click_1"));
					break;
				case 1:
					playAudio(_T("click_2"));
					break;
				case 2:
					playAudio(_T("click_3"));
					break;
				case 3:
					playAudio(_T("click_4"));
					break;
				}
				charIndex++;
				if (playerId == 1) {
					progress1 += 1;
				}
				else {
					progress2 += 1;
				}
				if (charIndex >= line.length()) {
					lineIndex++;
					charIndex = 0;
				}
			}
		}
	};
	void onExit() override {
		std::cout << "退出游戏场景" << std::endl;
	};
private:
	//倒计时计时器
	Timer countDownTimer;
	Camera cameraUI = Camera(Vector2D(1280, 720));
	Camera cameraPlayer = Camera(Vector2D(1280, 720));
	Player* player1;
	Player* player2;
};