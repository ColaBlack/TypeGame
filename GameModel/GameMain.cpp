#include"../libs/httplib.h"
#include<graphics.h>
#include"Scene.h"
#include"MenuScene.h"
#include"SelectorScene.h"
#include"GameScene.h"
#include"OverScene.h"
#include"SceneManager.h"
#include"loadResource.h"


Scene* gameScene = nullptr;
SceneManager sceneManager;
Camera mainCamera;

int main() {
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const int FPS = 60;

	// 初始化游戏
	loadResource();
	HWND hwnd = initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("该程序仅供学习使用，禁止商业用途！"));
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);
	gameScene = new GameScene();
	ExMessage msg;
	BeginBatchDraw();
	// 切换到游戏场景
	sceneManager.SetCurrentScene(gameScene);

	// 帧循环
	while (true) {

		DWORD frameStartTime = GetTickCount();

		// 事件循环
		while (peekmessage(&msg)) {
			sceneManager.onEvent(msg);
		}

		static DWORD lastTickTime = GetTickCount();
		DWORD currentTickTime = GetTickCount();
		sceneManager.onUpdate(currentTickTime - lastTickTime);
		lastTickTime = currentTickTime;

		setbkcolor(RGB(0, 0, 0));
		cleardevice();
		sceneManager.onDraw(mainCamera);

		FlushBatchDraw();

		DWORD frameEndTime = GetTickCount();
		// 稳定帧率为全局变量FPS
		if (1000 / FPS > (frameEndTime - frameStartTime)) {
			Sleep(1000 / FPS - (frameEndTime - frameStartTime));
		}
	}

	EndBatchDraw();

	return 0;
}
