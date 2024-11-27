#pragma once
#include"Atlas.h"
#include"AtlasUtils.h"

//玩家向左移动的图集
Atlas atlasPlayerLeft;

//玩家向右移动的图集
Atlas atlasPlayerRight;

void loadResource() {
	// todo: 在这里书写加载资源代码
	atlasPlayerLeft.loadFromFile(_T("resource\\player_left_%d.png"), 6);
	flipAtlas(atlasPlayerLeft, atlasPlayerRight);
}