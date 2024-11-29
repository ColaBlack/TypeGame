#pragma once
#include"Atlas.h"
#include"AtlasUtils.h"
#include"AudioUtils.h"

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

void loadResource() {
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

	//玩家1资源
	atlas1PIdleUp.loadFromFile(_T("resources/hajimi_idle_back_%d.png"), 1);
	atlas1PIdleDown.loadFromFile(_T("resources/hajimi_idle_front_%d.png"), 1);
	atlas1PIdleLeft.loadFromFile(_T("resources/hajimi_idle_left_%d.png"), 1);
	atlas1PIdleRight.loadFromFile(_T("resources/hajimi_idle_right_%d.png"), 1);
	atlas1PRunUp.loadFromFile(_T("resources/hajimi_run_back_%d.png"), 4);
	atlas1PRunDown.loadFromFile(_T("resources/hajimi_run_front_%d.png"), 4);
	atlas1PRunLeft.loadFromFile(_T("resources/hajimi_run_left_%d.png"), 4);
	atlas1PRunRight.loadFromFile(_T("resources/hajimi_run_right_%d.png"), 4);

	//玩家2资源
	atlas2PIdleUp.loadFromFile(_T("resources/manbo_idle_back_%d.png"), 1);
	atlas2PIdleDown.loadFromFile(_T("resources/manbo_idle_front_%d.png"), 1);
	atlas2PIdleLeft.loadFromFile(_T("resources/manbo_idle_left_%d.png"), 1);
	atlas2PIdleRight.loadFromFile(_T("resources/manbo_idle_right_%d.png"), 1);
	atlas2PRunUp.loadFromFile(_T("resources/manbo_run_back_%d.png"), 4);
	atlas2PRunDown.loadFromFile(_T("resources/manbo_run_front_%d.png"), 4);
	atlas2PRunLeft.loadFromFile(_T("resources/manbo_run_left_%d.png"), 4);
	atlas2PRunRight.loadFromFile(_T("resources/manbo_run_right_%d.png"), 4);

	//UI资源
	loadimage(&imageUI1, _T("resources/ui_1.png"));
	loadimage(&imageUI2, _T("resources/ui_2.png"));
	loadimage(&imageUI3, _T("resources/ui_3.png"));
	loadimage(&imageUIFight, _T("resources/ui_fight.png"));
	loadimage(&imageUITextbox, _T("resources/ui_textbox.png"));
	loadimage(&imageBackground, _T("resources/background.png"));

	//音频资源
	loadAudio(_T("resources/bgm.mp3"), _T("bgm"));
	loadAudio(_T("resources/1p_win.mp3"), _T("1p_win"));
	loadAudio(_T("resources/2p_win.mp3"), _T("2p_win"));
	loadAudio(_T("resources/click_1.mp3"), _T("click_1"));
	loadAudio(_T("resources/click_2.mp3"), _T("click_2"));
	loadAudio(_T("resources/click_3.mp3"), _T("click_3"));
	loadAudio(_T("resources/click_4.mp3"), _T("click_4"));
	loadAudio(_T("resources/ui_1.mp3"), _T("ui_1"));
	loadAudio(_T("resources/ui_2.mp3"), _T("ui_2"));
	loadAudio(_T("resources/ui_3.mp3"), _T("ui_3"));
	loadAudio(_T("resources/ui_fight.mp3"), _T("ui_fight"));

	std::ifstream file("config.cfg");

	if (!file.good()) {
		MessageBox(NULL, _T("配置文件config.cfg无法正常打开！"), _T("错误"), MB_ICONERROR);
		exit(-1);
	}

	std::stringstream strStream;
	strStream << file.rdbuf();
	address = strStream.str();

	file.close();
}