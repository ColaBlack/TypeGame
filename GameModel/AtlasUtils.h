#pragma once
#include"Atlas.h"
#include"ImgUtils.h"

// 水平翻转图集
void flipAtlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.getSize(); i++) {
		IMAGE flipedImg;
		flipImage(src.getImage(i), &flipedImg);
		dst.addImage(flipedImg);
	}
}