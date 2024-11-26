#include<graphics.h>
#include"Scene.h"
#include"MenuScene.h"

int main() {
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const int FPS = 60;

	// 初始化游戏
	initgraph(WIDTH, HEIGHT,EW_SHOWCONSOLE);
	ExMessage msg;
	BeginBatchDraw();

	Scene* currentScene = new MenuScene();
	currentScene->onEnter();

	// 帧循环
	while (true) {

		DWORD frameStartTime = GetTickCount();

		// 事件循环
		while (peekmessage(&msg)) {
			currentScene->onEvent(msg);
		}

		static DWORD lastTickTime = GetTickCount();
		DWORD currentTickTime = GetTickCount();
		currentScene->onUpdate(currentTickTime-lastTickTime);
		lastTickTime = currentTickTime;

		cleardevice();
		currentScene->onDraw();

		FlushBatchDraw();

		DWORD frameEndTime = GetTickCount();
		// 稳定帧率为全局变量FPS
		Sleep(max(0, (1000 / FPS) - (frameEndTime - frameStartTime)));
	}

	EndBatchDraw();

	return 0;
}