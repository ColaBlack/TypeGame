#include<graphics.h>
#include"Scene.h"
#include"MenuScene.h"
#include"SelectorScene.h"
#include"GameScene.h"
#include"OverScene.h"
#include"SceneManager.h"
#include"loadResource.h"


Scene* menuScene = nullptr;
Scene* selectorScene = nullptr;
Scene* gameScene = nullptr;
Scene* overScene = nullptr;
SceneManager sceneManager;
Camera mainCamera;

int main() {
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const int FPS = 60;

	// 初始化游戏
	loadResource();
	initgraph(WIDTH, HEIGHT, EW_SHOWCONSOLE);
	menuScene = new MenuScene();
	selectorScene = new SelectorScene();
	gameScene = new GameScene();
	overScene = new OverScene();
	ExMessage msg;
	BeginBatchDraw();

	// 切换到菜单场景
	sceneManager.SetCurrentScene(menuScene);

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

		cleardevice();
		sceneManager.onDraw(mainCamera);

		FlushBatchDraw();

		DWORD frameEndTime = GetTickCount();
		// 稳定帧率为全局变量FPS
		Sleep(max(0, (1000 / FPS) - (frameEndTime - frameStartTime)));
	}

	EndBatchDraw();

	return 0;
}