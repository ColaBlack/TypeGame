#include<graphics.h>

const int WIDTH = 1280;
const int HEIGHT = 720;
const int FPS = 60;

int main() {
	// 初始化游戏
	initgraph(WIDTH, HEIGHT);
	
	ExMessage msg;

	BeginBatchDraw();

	// 事件循环
	while (true) {

		DWORD frameStartTime = GetTickCount();

		while (peekmessage(&msg)) {

		}

		cleardevice();

		FlushBatchDraw();

		DWORD frameEndTime = GetTickCount();

		// 稳定帧率为全局变量FPS
		Sleep(max(0, (1000 / FPS) - (frameEndTime - frameStartTime)));
	}

	EndBatchDraw();

	return 0;
}